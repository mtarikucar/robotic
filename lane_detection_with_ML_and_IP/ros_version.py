#!/usr/bin/env python
#-*-coding: utf-8 -*-

##################################################################
#            How is the place where there is no time?            #
#            Is the rest an uninterrupted moment?                #
# author: Necip Fazıl Kısakürek                                  #
##################################################################

# author: Muhammed Tarık Uçar
#todo: 
    #perspective transform section should be dynamic by frame size
    #decide the prediction type in the detect line features KMeans or hierartical
    #dynamic cluster count in deteciton function
    #decide the which one to use lcm or constant variable in get_points 
    #share the procceses with cuda #

import rospy
import cv2
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import math
from sklearn.cluster import AgglomerativeClustering
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError


def perspective_transform(cv_image):
    ysize = cv_image.shape[0]
    xsize = cv_image.shape[1]


    src = np.float32([
    (66,478),
    (537,477),
    (439,298),
    (180,296)
    ])

    dst = np.float32([
    (122,480),
    (488,480),
    (488,190),
    (122,190)
    ])
    matrix = cv2.getPerspectiveTransform(src, dst)

    return cv2.warpPerspective(cv_image, matrix, (xsize, ysize))

def edge_detect(img):
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    img_blur = cv2.GaussianBlur(img_gray, (3,3), 0)
    img_blur = cv2.medianBlur(img, ksize = 7)
    """ 
    sobelx = cv2.Sobel(src=img_blur, ddepth=cv2.CV_64F, dx=1, dy=0, ksize=5) # Sobel Edge
    sobely = cv2.Sobel(src=img_blur, ddepth=cv2.CV_64F, dx=0, dy=1, ksize=5) # Sobel Edge
    sobelxy = cv2.Sobel(src=img_blur, ddepth=cv2.CV_64F, dx=1, dy=1, ksize=5) # Combined X 
    """
    edges = cv2.Canny(image=img_blur, threshold1=100, threshold2=200) # Canny Edge Detection
    
    return edges

def get_point(image):
    M = cv2.moments(image)
    if M['m00'] > 0:
        cx = int(M['m10']/M['m00'])
        cy = int(M['m01']/M['m00'])
        return cx,cy
    return -1,-1

def get_points(image):
    gcd = math.gcd(image.shape[1],image.shape[0])
    lcm = image.shape[1]*int(image.shape[0]/gcd)
    lcm = 30 # bu kısım silinecek
    points_X = np.array([])
    points_Y = np.array([])
    for y in range(0,image.shape[0],lcm):
        for x in range(0,image.shape[1],lcm):
            point_X,point_Y = get_point(image[y:y+lcm,x:x+lcm])
            if(point_X != -1):
                points_X = np.append(points_X,point_X + x)
                points_Y = np.append(points_Y,point_Y + y)
            
    return points_X,points_Y

def manuel_points(points):
    right_points = []
    left_points = []
    for j in points:
        if j[0] > width/2:
            right_points.append(j)
        elif j[0] < width/2:
            left_points.append(j)
    pointx = []
    pointy = []
    for j in left_points:
        if j != 0:
            pointy.append(480 - j[1])
            pointx.append(j[0]) 
    plt.plot(pointx, pointy, "o") 
    pointx = []
    pointy = []
    for j in right_points:
        if j != 0:
            pointy.append(480 - j[1])
            pointx.append(j[0])
    plt.plot(pointx, pointy, "o")
    plt.show()

def detect_line_and_predict(points_X,points_Y):
    dictionary = {"x":points_X,"y":points_Y}
    data = pd.DataFrame(dictionary)

    hierartical_cluster = AgglomerativeClustering(n_clusters = 2,affinity= "euclidean",linkage = "ward")
    cluster = hierartical_cluster.fit_predict(data)
    data["label"] = cluster

    plt.scatter(data.x[data.label == 0],data.y[data.label == 0],color="blue")
    plt.scatter(data.x[data.label == 1],data.y[data.label == 1],color="orange")
    #plt.scatter(AgglomerativeClustering.cluster_centers_[:,0],kmeans2.cluster_centers_[:,1],color = "yellow")
    for line in range(2):
        points_X = data.x[data.label == line].values.reshape(-1,1)
        points_Y = data.y[data.label == line].values.reshape(-1,1)

        polynomial_regression = PolynomialFeatures(degree = 2)
        x_polynomial = polynomial_regression.fit_transform(points_X)
        regresison = LinearRegression()
        regresison.fit(x_polynomial,points_Y)
        
        y_head2 = regresison.predict(x_polynomial)
        plt.plot(points_X,y_head2,color= "green",label = "poly")
        plt.legend()


def callback(img):
	
	frame = bridge.imgmsg_to_cv2(img, "bgr8")

	bird_eye = perspective_transform(frame)
	edge_img = edge_detect(bird_eye)
	points_X,points_Y = get_points(edge_img)
	detect_line_and_predict(points_X,points_Y)
	plt.show()

	if cv2.waitKey(1) & 0xFF == ord('q'):
		rospy.signal_shutdown('kapatiliyor...')


def kill():
    rospy.loginfo('terminated')

if __name__ == "__main__":
    
    rospy.init_node('lane',anonymous=True)
    
    bridge = CvBridge()
    
    rospy.loginfo('CTRL+C to terminate')    
    rospy.on_shutdown(kill)
    
    rospy.Subscriber("/usb_cam/image_raw", Image, callback, queue_size = 1)
    rospy.spin()
