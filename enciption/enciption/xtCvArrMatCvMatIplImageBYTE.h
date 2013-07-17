#pragma once
class xtCvArrMatCvMatIplImageBYTE
{
public:
	xtCvArrMatCvMatIplImageBYTE(void);
	~xtCvArrMatCvMatIplImageBYTE(void);
};

/****
һ��Mat���ͣ��������ͣ�Matrix��

    ��openCV�У�Mat��һ����ά���ܼ��������顣�����������������;���ͼ��ֱ��ͼ�ȵȳ����Ķ�ά���ݡ�

    Mat��3����Ҫ�ķ�����

         1��Mat mat = imread(const String* filename);            ��ȡͼ��

         2��imshow(const string frameName, InputArray mat);      ��ʾͼ��

         3��imwrite (const string& filename, InputArray img);    ����ͼ��

    Mat���ͽ�CvMat��IplImage������˵���и�ǿ�ľ�������������֧�ֳ����ľ������㡣�ڼ����ܼ��͵�Ӧ�õ��У�
	��CvMat��IplImage����ת��ΪMat���ͽ������ټ���ʱ�仨�ѡ�

A.Mat -> IplImage
ͬ��ֻ�Ǵ���ͼ��ͷ����û�и������ݡ�
���� // ����Mat���͵�imgMatͼ�����ݴ���
IplImage pImg= IplImage(imgMat); 

B.Mat -> CvMat
��IplImage��ת�����ƣ����������ݣ�ֻ��������ͷ��
���� // ����Mat���͵�imgMatͼ�����ݴ���
     CvMat cvMat = imgMat;

����CvMat������IplImage���ͣ���ͼ������

       ��openCV�У�Mat������CvMat��IplImage���Ͷ����Դ������ʾͼ��
���ǣ�Mat���Ͳ����ڼ��㣬��ѧ�Խϸߣ�openCV��Mat���͵ļ���Ҳ�������Ż���
��CvMat��IplImage���͸������ڡ�ͼ�񡱣�openCV�����е�ͼ�����
�����š���ͨ����ȡ��ͼ����ֵ�����ȣ��������Ż���
���䣺IplImage��CvMat��������CvMat��CvArr������CvArr -> CvMat -> IplImage
            CvArr���������Ĳ��������۴������CvMat��IplImage���ڲ����ǰ�CvMat����

1.CvMat
A.CvMat-> IplImage
IplImage* img = cvCreateImage(cvGetSize(mat),8,1);
cvGetImage(matI,img);
cvSaveImage("rice1.bmp",img);

B.CvMat->Mat
��IplImage��ת�����ƣ�����ѡ���Ƿ������ݡ�
Mat::Mat(const CvMat* m, bool copyData=false);
��openCV�У�û��������vector�������ݽṹ���κ�ʱ�򣬵�����Ҫ��ʾ����ʱ���þ������ݱ�ʾ���ɡ�
���ǣ�CvMat���������������Դ����γ���ѧ������������ȣ������󣬱���CvMat��Ԫ����������
���������ڻ����������ͣ����磬���洴��һ����ά���ݾ���

              CvMat* cvCreatMat(int rows ,int cols , int type);

�����type�����������Ԥ�����������ͣ�����RGB���߱�Ķ�ͨ�����ݡ��������Ǳ������
һ��CvMat�����ϱ�ʾ�ḻ��ʵ�ͼ���ˡ�

2.IplImage
�����͹�ϵ�ϣ����ǿ���˵IplImage���ͼ̳���CvMat���ͣ���Ȼ�����������ı�����֮������ͼ�����ݡ�
IplImage���ͽ�֮CvMat���˺ܶ����������depth��nChannels������ͨ�ľ������͵��У�
ͨ����Ⱥ�ͨ������ͬʱ��ʾ������32λ��ʾRGB+Alpha.���ǣ���ͼ�����У��������������
��ͨ�����ֿ�������������OpenCV��ͼ���ʾ��һ���Ż�������

IplImage�Ķ�ͼ�����һ���Ż��Ǳ���origin----ԭ�㡣�ڼ�����Ӿ������ϣ�һ����Ҫ�Ĳ���
�Ƕ�ԭ��Ķ��岻�����ͼ����Դ�������ʽ����������ϵͳ�����ԭ�ص�ѡȡ����Ӱ�졣
Ϊ���ֲ���һ�㣬openCV�����û������Լ���ԭ�����á�ȡֵ0��ʾԭ��λ��ͼƬ���Ͻǣ�1��ʾ���½ǡ�

dataOrder�����������ݵĸ�ʽ����IPL_DATA_ORDER_PIXEL��IPL_DATA_ORDER_PLANE����ȡֵ��
ǰ�߱��Ƕ������أ���ͬ��ͨ�������ݽ������У����߱�ʾ����ͨ����˳��ƽ�����С�

IplImage���͵����ж���������Ƕԡ�ͼ�񡱵ı�ʾ������������Ż���

A.IplImage -> Mat

IplImage* pImg = cvLoadImage("lena.jpg");
Mat img(pImg,0); // 0�ǲ��}�uӰ��Ҳ����pImg�cimg��data����ͬ��ӛ���wλ�ã�header������
B.IplImage -> CvMat

��1��CvMat mathdr, *mat = cvGetMat( img, &mathdr );
��2��CvMat *mat = cvCreateMat( img->height, img->width, CV_64FC3 );
  cvConvert( img, mat );

C.IplImage*-> BYTE*

BYTE* data= img->imageData;
CvMat��IplImage����ʱ��һ��С����

1����������ʱ����һ������Ϊ�������ڶ�������Ϊ������

CvMat* cvCreateMat( int rows, int cols, int type );

2������ͼ��ʱ��CvSize��һ������Ϊ��ȣ����������ڶ�������Ϊ�߶ȣ����������� ����CvMat���������෴��

IplImage* cvCreateImage(CvSize size, int depth, int channels );

CvSize cvSize( int width, int height );

 

IplImage�ڲ�bufferÿ���ǰ�4�ֽڶ���ģ�CvMatû���������

 

���䣺

A.BYTE*-> IplImage*
img= cvCreateImageHeader(cvSize(width,height),depth,channels);
cvSetData(img,data,step);

//������cvCreateImageHeader()����IplImageͼ��ͷ���ƶ�ͼ��ĳߴ磬��Ⱥ�ͨ������
//Ȼ����cvSetData()����BYTE*ͼ������ָ������IplImageͼ��ͷ���������ݣ�
//����stepָ����IplImageͼ��ÿ��ռ���ֽ���������1ͨ����IPL_DEPTH_8Uͼ��
step���Ե���width��

****/