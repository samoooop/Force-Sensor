import numpy as np
import cv2

cap = cv2.VideoCapture(1)

showFrame = True

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()

    # Our operations on the frame come here
    # gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Display the resulting frame
    if showFrame:
        cv2.imshow('frame',frame)
    else : #show delta
        diff = cv2.absdiff(base, frame)
        cv2.imshow('frame',diff);
    key = cv2.waitKey(1) & 0xFF
    if key == ord('c'):
        base = frame
    if key == ord('s'):
        showFrame = not showFrame
    if key == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()