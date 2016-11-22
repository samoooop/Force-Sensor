import cv2

img_1 = cv2.imread("my_photo-274.jpg");
img_2 = cv2.imread("my_photo-273.jpg");

print(img_1.shape);

dim_1 = img_1.shape;

from_x = dim_1[1]*0.43;
to_x = dim_1[1]*0.65;
from_y = dim_1[0]*0.5;
to_y = dim_1[0]*0.8;

img_1_crop = img_1[from_y:to_y,from_x:to_x];
img_2_crop = img_2[from_y:to_y,from_x:to_x];

cv2.imshow("ori",img_1_crop);
cv2.imshow("sam",img_2_crop);
cv2.waitKey(0);

cv2.imwrite("with_obj.jpg",img_2_crop);
cv2.imwrite("without_obj.jpg",img_1_crop);