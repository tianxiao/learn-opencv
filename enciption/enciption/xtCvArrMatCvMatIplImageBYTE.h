#pragma once
class xtCvArrMatCvMatIplImageBYTE
{
public:
	xtCvArrMatCvMatIplImageBYTE(void);
	~xtCvArrMatCvMatIplImageBYTE(void);
};

/****
一、Mat类型：矩阵类型，Matrix。

    在openCV中，Mat是一个多维的密集数据数组。可以用来处理向量和矩阵、图像、直方图等等常见的多维数据。

    Mat有3个重要的方法：

         1、Mat mat = imread(const String* filename);            读取图像

         2、imshow(const string frameName, InputArray mat);      显示图像

         3、imwrite (const string& filename, InputArray img);    储存图像

    Mat类型较CvMat与IplImage类型来说，有更强的矩阵运算能力，支持常见的矩阵运算。在计算密集型的应用当中，
	将CvMat与IplImage类型转化为Mat类型将大大减少计算时间花费。

A.Mat -> IplImage
同样只是创建图像头，而没有复制数据。
例： // 假设Mat类型的imgMat图像数据存在
IplImage pImg= IplImage(imgMat); 

B.Mat -> CvMat
与IplImage的转换类似，不复制数据，只创建矩阵头。
例： // 假设Mat类型的imgMat图像数据存在
     CvMat cvMat = imgMat;

二、CvMat类型与IplImage类型：“图像”类型

       在openCV中，Mat类型与CvMat和IplImage类型都可以代表和显示图像，
但是，Mat类型侧重于计算，数学性较高，openCV对Mat类型的计算也进行了优化。
而CvMat和IplImage类型更侧重于“图像”，openCV对其中的图像操作
（缩放、单通道提取、图像阈值操作等）进行了优化。
补充：IplImage由CvMat派生，而CvMat由CvArr派生即CvArr -> CvMat -> IplImage
            CvArr用作函数的参数，无论传入的是CvMat或IplImage，内部都是按CvMat处理。

1.CvMat
A.CvMat-> IplImage
IplImage* img = cvCreateImage(cvGetSize(mat),8,1);
cvGetImage(matI,img);
cvSaveImage("rice1.bmp",img);

B.CvMat->Mat
与IplImage的转换类似，可以选择是否复制数据。
Mat::Mat(const CvMat* m, bool copyData=false);
在openCV中，没有向量（vector）的数据结构。任何时候，但我们要表示向量时，用矩阵数据表示即可。
但是，CvMat类型与我们在线性代数课程上学的向量概念相比，更抽象，比如CvMat的元素数据类型
并不仅限于基础数据类型，比如，下面创建一个二维数据矩阵：

              CvMat* cvCreatMat(int rows ,int cols , int type);

这里的type可以是任意的预定义数据类型，比如RGB或者别的多通道数据。这样我们便可以在
一个CvMat矩阵上表示丰富多彩的图像了。

2.IplImage
在类型关系上，我们可以说IplImage类型继承自CvMat类型，当然还包括其他的变量将之解析成图像数据。
IplImage类型较之CvMat多了很多参数，比如depth和nChannels。在普通的矩阵类型当中，
通常深度和通道数被同时表示，如用32位表示RGB+Alpha.但是，在图像处理中，我们往往将深度
与通道数分开处理，这样做是OpenCV对图像表示的一种优化方案。

IplImage的对图像的另一种优化是变量origin----原点。在计算机视觉处理上，一个重要的不便
是对原点的定义不清楚，图像来源，编码格式，甚至操作系统都会对原地的选取产生影响。
为了弥补这一点，openCV允许用户定义自己的原点设置。取值0表示原点位于图片左上角，1表示左下角。

dataOrder参数定义数据的格式。有IPL_DATA_ORDER_PIXEL和IPL_DATA_ORDER_PLANE两种取值，
前者便是对于像素，不同的通道的数据交叉排列，后者表示所有通道按顺序平行排列。

IplImage类型的所有额外变量都是对“图像”的表示与计算能力的优化。

A.IplImage -> Mat

IplImage* pImg = cvLoadImage("lena.jpg");
Mat img(pImg,0); // 0是不複製影像，也就是pImg與img的data共用同個記憶體位置，header各自有
B.IplImage -> CvMat

法1：CvMat mathdr, *mat = cvGetMat( img, &mathdr );
法2：CvMat *mat = cvCreateMat( img->height, img->width, CV_64FC3 );
  cvConvert( img, mat );

C.IplImage*-> BYTE*

BYTE* data= img->imageData;
CvMat和IplImage创建时的一个小区别：

1、建立矩阵时，第一个参数为行数，第二个参数为列数。

CvMat* cvCreateMat( int rows, int cols, int type );

2、建立图像时，CvSize第一个参数为宽度，即列数；第二个参数为高度，即行数。这 个和CvMat矩阵正好相反。

IplImage* cvCreateImage(CvSize size, int depth, int channels );

CvSize cvSize( int width, int height );

 

IplImage内部buffer每行是按4字节对齐的，CvMat没有这个限制

 

补充：

A.BYTE*-> IplImage*
img= cvCreateImageHeader(cvSize(width,height),depth,channels);
cvSetData(img,data,step);

//首先由cvCreateImageHeader()创建IplImage图像头，制定图像的尺寸，深度和通道数；
//然后由cvSetData()根据BYTE*图像数据指针设置IplImage图像头的数据数据，
//其中step指定该IplImage图像每行占的字节数，对于1通道的IPL_DEPTH_8U图像，
step可以等于width。

****/