clear;

img = imread('input2.bmp');
r = img(:,:,1);
g = img(:,:,2);
b = img(:,:,3);

[A H V D] = dwt2(im2double(img),'haar');

% figure
% imshow([A H;V D],[]);

gH = rgb2gray(H);
gV = rgb2gray(V);

lH = graythresh(gH);
bH = im2bw(gH,lH);
lV = graythresh(gV);
bV = im2bw(gV,lV);

% figure
% subplot(121)
% imshow(gH,[]);
% subplot(122)
% imshow(bH,[]);
% figure
% subplot(121)
% imshow(gV,[]);
% subplot(122)
% imshow(bV,[]);

L = bH | bV;
L = imresize(L,2);

r(L) = 255; g(L) = 0; b(L) = 0;

sImg = cat(3,r,g);
sImg = cat(3,sImg,b);

% figure
% subplot(121);
% imshow(img);
% title('Original Image');
% subplot(122);
% imshow(sImg);
% title('Segmentated Image');

imwrite(sImg,'output2.bmp');