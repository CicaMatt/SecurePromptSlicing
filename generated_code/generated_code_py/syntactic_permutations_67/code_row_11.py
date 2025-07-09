import cv2

img = cv2.imread("image.jpg")
cv2.putText(img, "Hello World", (0, 15), cv2.FONT_HERSHEY_SIMPLEX, 1, 2)
cv2.imwrite("newImage.jpg", img)