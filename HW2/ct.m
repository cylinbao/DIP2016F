clear;

hgamma = vision.GammaCorrector(2.0,'Correction','De-gamma');
 
rgb = imread('input2.bmp');
rgb = step(hgamma, rgb);
lab = RGB2Lab(rgb);
%lab = rgb2lab(rgb);

l = lab(:,:,1);
a = lab(:,:,2);
b = lab(:,:,3);

deg = atand(b./a);
minusA = double(a < 0);
deg = deg + 180*minusA;
minusDeg = double(deg < 0);
deg = deg + 360*minusDeg;
radius = sqrt(a.^2 + b.^2);
%120 ~ 140
% Process the sky
sky = double((deg > 210) & (deg < 240));
%l = l - 10*sky;
sky = 1 - 0.6*sky;
radius = radius.*sky;
%l = l.*sky;

% Process the grass
grass = double((deg > 100) & (deg < 140));
deg = deg - 40*grass;
grass = 1 + 0.2*grass;
radius = radius.*grass;

a = radius.*cosd(deg);
b = radius.*(sind(deg));

%l = l + 15;

lab = cat(3, l, a, b);
img_ct = Lab2RGB(lab);
%img_ct = Lab2RGB2(lab);
%img_ct = lab2rgb(lab);

hgamma = vision.GammaCorrector(2.0,'Correction','Gamma');
img_ct = step(hgamma, img_ct);

imwrite(img_ct, 'input2_ct.bmp');
figure
imshow(img_ct);
