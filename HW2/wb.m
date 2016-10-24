clear;

img=imread('input1.bmp');

%figure
%histogram(img);
%figure
%imshow(img);

redp = img(:,:,1);
greenp = img(:,:,2);
bluep = img(:,:,3);

redMean = mean(mean(redp));
greenMean = mean(mean(greenp));
blueMean = mean(mean(bluep));
avg = (redMean+greenMean+blueMean)/3;

redp = (avg/redMean)*redp;
greenp = (avg/greenMean)*greenp;
bluep = (avg/blueMean)*bluep;

img_wb = cat(3, redp, greenp, bluep);
imwrite(img_wb, 'input1_wb.bmp');
%figure
%histogram(img_wb);
%figure
%imshow(img_wb);
