檔案結構:
本次作業分三個Parts,分別是Image input/output, Resolution and Scaling
因此我開了三個同名的資料夾， 把三個Task不同的Controling程式碼放在對應的資料夾裡

不過主要的檔案是Top目錄下的bmp.h，裡面有所有用到的函式
三個主程式都會來include這個header file
因此我的三個主程式都相當短小，他們分別只是來呼叫幾個不同在bmp.h所定義的函式

執行方法:
Image input/output:
到ImageInputOutput資料夾下，執行make以產生執行檔，或是自己手動用gcc編譯也可以
接著執行它 ./imgRWbmp

Resolution:
到Resolution資料夾下，執行make以產生執行檔，或是自己手動用gcc編譯也可以
接著執行它 ./imgQR

Scaling:
到Scaling資料夾下，執行make以產生執行檔，或是自己手動用gcc編譯也可以
接著執行它 ./imgScaling
