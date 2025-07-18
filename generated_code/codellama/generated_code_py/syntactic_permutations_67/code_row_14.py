import cv2

image_file = "img.jpg"

# Load image
img = cv2.imread(image_file)

# Save image
cv2.imwrite("saved_img.jpg", img)

print("Image saved successfully.")