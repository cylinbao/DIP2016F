clear;

rgb = imread('input3.bmp');
lab = rgb2lab(rgb);
sigma = 10;

l = lab(:,:,1);

l = homoFilt(l, sigma);

lab(:,:,1) = l;

outrgb = lab2rgb(lab);

subplot(121)
imshow(rgb);
subplot(122)
imshow(outrgb);
