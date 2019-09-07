#python name_of_the_file.py --face cascades/haarcascade_frontalface_default.xml

# import the necessary packages
import argparse
import cv2
import numpy  as np
import imutils

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-f","--face",required = True,help="frontal face cascade classifier path")
ap.add_argument("-i", "--image", help="Path to the image")
args = vars(ap.parse_args())

detector = cv2.CascadeClassifier(args["face"])
if not args.get("image", False):
	camera = cv2.VideoCapture(0)
	while True:
		(return_value, frame)=camera.read()
		frame = imutils.resize(frame, width=400)
		gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
		faceRects = detector.detectMultiScale(gray, scaleFactor=1.05, minNeighbors=5,minSize=(30, 30), flags=cv2.CASCADE_SCALE_IMAGE)
		for (x, y, w, h) in faceRects:
			cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
			image = frame[ y:y+h , x:x+w]
			image=imutils.resize(image,width=48)
		cv2.imshow("camera",frame)
		key = cv2.waitKey(1) & 0xFF
		if key == ord("c") :
			break
	camera.release()
	cv2.destroyAllWindows()
 
(h,w)=image.shape[:2]
threshold=int(input('Enter the threshold : '))
print("width: {w} pixels".format(w=image.shape[1]))
print("height: {h}  pixels".format(h=image.shape[0]))
print("channels: {c}".format(c=image.shape[2]))
#you could even blur the image before this using the commands
#blurred = cv2.GaussianBlur(image, (15,15), 0)
#cv2.imshow("blur",blurred)
f=cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
k=np.float32([[0,0,0,0,-0.25,0,0,0,0],[0,0,0,-0.25,-0.5,-0.25,0,0,0],[0,0,-0.25,-0.5,-0.75,-0.5,-0.25,0,0],[0,-0.25,-0.5,-0.75,-1,-0.75,-0.5,-0.25,0],[0,0,0,0,0,0,0,0,0],[0,0.25,0.5,0.75,1,0.75,0.5,0.25,0],[0,0,0.25,0.5,0.75,0.5,0.25,0,0],[0,0,0,0.25,0.5,0.25,0,0,0],[0,0,0,0,0.25,0,0,0,0]])
k1=np.float32([[0,0,0,-0.125,0,0.125,0,0,0],[0,0,-0.125,-0.25,0,0.25,0.125,0,0],[0,0,-0.25,-0.5,0,0.5,0.25,0,0],[0,-0.25,-0.5,-0.75,0,0.75,0.5,0.25,0],[-0.25,-0.5,-0.75,-1,0,1,0.75,0.5,0.25],[0,-0.25,-0.5,-0.75,0,0.75,0.5,0.25,0],[0,0,-0.25,-0.5,0,0.5,0.25,0,0],[0,0,-0.125,-0.25,0,0.25,0.125,0,0],[0,0,0,-0.125,0,0.125,0,0,0]])
#yy=np.float32([[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1],[-1,-1,-1,-1,0,1,1,1,1]])
sas1=np.float32([[-1,-1,-1],[0,0,0],[1,1,1]])
sas2=np.float32([[1,0,-1],[1,0,-1],[1,0,-1]])
imag2=np.zeros(image.shape[:2],dtype="uint8")
imag3=np.zeros(image.shape[:2],dtype="uint8")
imag4=np.zeros([int(h/2),int(w/2)],dtype="uint8")
imag5=np.zeros([int(h/2),int(w/2)],dtype="uint8")
imag7=np.zeros([int(h/4),int(w/4)],dtype="uint8")
imag8=np.zeros([int(h/4),int(w/4)],dtype="uint8")
sum=0
cv2.imshow("original",image)
cv2.waitKey(0)
print (k)
print(k1)

for i in range(0,h-3):
	for j in range(0,w-3):
		for m in range(3):
			for n in range(3):

					y=int(sas1[m][n])
					u=int(f[i+m,j+n])

					sum=sum+(u*y)
		#print(sum)	
		#for m in range(9):
		if sum>threshold :
			imag2[i+1,j+1]=sum
		sum=0
cv2.imshow("Horizontaledges",imag2)
cv2.waitKey(0)
for i in range(0,h-3):
	for j in range(0,w-3):
		for m in range(3):
			for n in range(3):

					y=int(sas2[m][n])
					u=int(f[i+m,j+n])

					sum=sum+(u*y)
		#print(sum)
		#for m in range(9):
		if sum>threshold :
			imag3[i+1,j+1]=sum
		sum=0

for i in range(0,int(h),2):
	for j in range(0,int(w),2):
		list1=[int(imag2[i,j]),int(imag2[i+1,j]),int(imag2[i,j+1]),int(imag2[i+1,j+1])]
		list1.sort()
		imag4[int(i/2),int(j/2)]=int(list1[-1])
for i in range(0,int(h),2):
	for j in range(0,int(w),2):
		list1=[int(imag3[i,j]),int(imag3[i+1,j]),int(imag3[i,j+1]),int(imag3[i+1,j+1])]
		list1.sort()
		imag5[int(i/2),int(j/2)]=list1[-1]
for i in range(0,int(h/2),2):
	for j in range(0,int(w/2),2):
		list1=[int(imag4[i,j]),int(imag4[i+1,j]),int(imag4[i,j+1]),int(imag4[i+1,j+1])]
		list1.sort()
		imag7[int(i/2),int(j/2)]=list1[-1]	
for i in range(0,int(h/2),2):
	for j in range(0,int(w/2),2):
		list1=[int(imag5[i,j]),int(imag5[i+1,j]),int(imag5[i,j+1]),int(imag5[i+1,j+1])]
		list1.sort()
		imag8[int(i/2),int(j/2)]=list1[-1]		
cv2.imshow("pooling1",imag4)
cv2.waitKey(0)
cv2.imshow("pooling2",imag5)
cv2.waitKey(0)
cv2.imshow("verticaledges",imag3)
cv2.waitKey(0)
krish=cv2.add(imag3,imag2)
cv2.imshow("both",krish)
cv2.waitKey(0)
gh=cv2.bitwise_not(imag2)
uip=cv2.bitwise_and(gh,gh,mask=f)
# show the image and wait for a keypress
cv2.imshow("Image",uip)
cv2.waitKey(0)
fre=open('krish123.txt','w+')
for i in range(int(h/4)):
	for j in range(int(w/4)):
		o=str(imag7[i,j])
		fre.write(o)
		fre.write("\t")
	fre.write('\n')
fre.write("^\n")
for i in range(int(h/4)):
	for j in range(int(w/4)):
		o=str(imag8[i,j])
		fre.write(o)
		fre.write("\t")
	fre.write('\n')
fre.write('--\n')

cv2.imwrite("newimage.jpg", krish)
