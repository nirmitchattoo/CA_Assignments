import cv2
import numpy as np
import math
import matplotlib.pyplot as plt
pic2 = cv2.imread("pic2.jpg")
pic2 = cv2.resize(pic2,(400,400))
s  = pic2.shape
cv2.imshow('Original',pic2)
pic2Gray = cv2.cvtColor(pic2,cv2.COLOR_BGR2GRAY)
pic2Gray = cv2.convertScaleAbs(pic2Gray,alpha=1.10 , beta=-20)
cv2.imshow('Binary',pic2Gray)
def Hist(image):
    H = np.zeros(shape=(256,1))
    s  = image.shape
    for i in range(s[0]):
        for j in range(s[1]):
            k = image[i,j]
            H[k,0] = H[k,0] + 1
    return H
histg = Hist(pic2Gray)
plt.plot(histg)
x = histg.reshape(1,256)
y = np.array([])
y = np.append(y,x[0,0])
for i in range(255):
    k = x[0,i+1]+y[i]
    y = np.append(y,k)
y = np.round((y/(s[0]*s[1]))*(256-1))
for i in range(s[0]):
    for j in range(s[1]):
        k = pic2Gray[i,j]
        pic2Gray[i,j] = y[k]
equal = Hist(pic2Gray)
cv2.imshow("myequalize",pic2Gray)
plt.plot(equal)
plt.show()
cv2.waitKey(0)
