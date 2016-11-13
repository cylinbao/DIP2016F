clear;

inImg = imread('input3.bmp');
sigma = 10;

r = inImg(:,:,1);
g = inImg(:,:,2);
b = inImg(:,:,3);

outImg(:,:,1) = homoFilt(r, sigma);
outImg(:,:,2) = homoFilt(g, sigma);
outImg(:,:,3) = homoFilt(b, sigma);

subplot(121)
imshow(inImg);
subplot(122)
imshow(outImg);
