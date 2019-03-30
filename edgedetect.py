# USAGE
# open cmd
# type cd c:\python\python37-32\src
# then type
# python edgedetect.py -i ner.png

# import the necessary packages
import argparse
import cv2
import numpy  as np

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--image", required=True, help="Path to the image")
args = vars(ap.parse_args())

# load the image and show some basic information on it
image = cv2.imread(args["image"])
(h,w)=image.shape[:2]
print("width: {w} pixels".format(w=image.shape[1]))
print("height: {h}  pixels".format(h=image.shape[0]))
print("channels: {c}".format(c=image.shape[2]))
#you could even blur the image before this using the commands
#blurred = cv2.GaussianBlur(image, (15,15), 0)
#cv2.imshow("blur",blurred)
f=cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
k=np.int32([[-1,-1,-1,-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1,-1,-1,-1],[0,0,0,0,0,0,0,0,0],[1,1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1,1]])

yy=np.int32([[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1]])
imag2=np.zeros(image.shape[:2],dtype="uint8")
imag3=np.zeros(image.shape[:2],dtype="uint8")
sum=0
cv2.imshow("original",image)
cv2.waitKey(0)

for i in range(0,h-9,9):
	for j in range(0,w-9,9):
		for m in range(9):
			for n in range(9):

					y=int(k[m][n])
					u=int(f[i+m,j+n])

					sum=sum+(u*y)
		#print(sum)	
		for m in range(9):
				imag2[i+4,j+m]=sum
		sum=0
for i in range(0,h-9,9):
	for j in range(0,w-9,9):
		for m in range(9):
			for n in range(9):

					y=int(yy[m][n])
					u=int(f[i+m,j+n])

					sum=sum+(u*y)
		#print(sum)
		for m in range(9):
				imag3[i+m,j+4]=sum
		sum=0
cv2.imshow("Verticaledges",imag2)
cv2.waitKey(0)
cv2.imshow("horizontaledges",imag3)
cv2.waitKey(0)
krish=cv2.add(imag3,imag2)
cv2.imshow("both",krish)
cv2.waitKey(0)
#gh=cv2.bitwise_not(imag2)
#uip=cv2.bitwise_and(gh,gh,mask=f)
# show the image and wait for a keypress
#cv2.imshow("Image",uip)
cv2.waitKey(0)

# save the image -- OpenCV handles converting filetypes
# automatically
cv2.imwrite("newimage.jpg", krish)
