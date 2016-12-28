clear;

img = imread('input2.bmp');
r = img(:,:,1);
g = img(:,:,2);
b = img(:,:,3);
gImg = rgb2gray(img);

[A1 H1 V1 D1] = dwt2(gImg,'haar');
[A2 H2 V2 D2] = dwt2(A1,'haar');

wH2 = idwt2(H2,H2,H2,H2,'haar');
wH1 = idwt2(wH2,H1,V1,D1,'haar');
bH = wH1 > 20;

wV2 = idwt2(V2,V2,V2,V2,'haar');
wV1 = idwt2(wV2,H1,V1,D1,'haar');
bV = wV1 > 20;

figure
subplot(121)
imshow(wH1,[]);
title('Horizeontal Image');
subplot(122)
imshow(bH,[]);
title('Horizontal Edges');
figure
subplot(121)
imshow(wV1,[]);
title('Vertical Image');
subplot(122)
imshow(bV,[]);
title('Vertical Edges');

r(bH) = 255; g(bH) = 0; b(bH) = 0;
r(bV) = 255; g(bV) = 0; b(bV) = 0;

sImg = cat(3,r,g);
sImg = cat(3,sImg,b);

imwrite(sImg,'outpu2.bmp');

figure
subplot(121);
imshow(img);
title('Original Image');
subplot(122);
imshow(sImg);
title('Segmentated Image');