clear;

img = imread('input1.bmp');

[A1 H1 V1 D1] = dwt2(im2double(img),'haar');
[A2 H2 V2 D2] = dwt2(A1,'haar');
[A3 H3 V3 D3] = dwt2(A2,'haar');

% Do some proccessing on [A H V D] here
D1(:) = 0;
D2(:) = 0;
D3(:) = 0;

dImg3 = idwt2(A3,H3,V3,D3,'haar');
dImg2 = idwt2(dImg3,H2,V2,D2,'haar');
dImg1 = idwt2(dImg2,H1,V1,D1,'haar');
