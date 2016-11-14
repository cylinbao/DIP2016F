function [out] = imgeh(rgb, gsigma, shrad, shamo)

figure();
subplot(221)
imshow(rgb);
title('original');

outHis(:,:,1) = histeq(rgb(:,:,1));
outHis(:,:,2) = histeq(rgb(:,:,2));
outHis(:,:,3) = histeq(rgb(:,:,3));

subplot(222)
imshow(outHis);
title('histogram equalization');

outBlur = imgaussfilt(outHis,gsigma);
subplot(223)
imshow(outBlur);
title('blur');

out = imsharpen(outBlur,'Radius',shrad,'Amount',shamo);
subplot(224)
imshow(out);
title('sharpen');

end