// Video.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

extern "C" {
    #ifndef __STDC_CONSTANT_MACROS
    #define __STDC_CONSTANT_MACROS
    #endif
    #include <libavcodec\avcodec.h>
    #include <libavformat\avformat.h>
    #include <libswscale\swscale.h>
    #include <libavutil\avutil.h>
}

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swscale.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	AVCodec *codec;
	AVCodecContext *c = NULL;
	uint8_t outbuf;
	int i, out_size, outbuf_size;

	//Registra todos os formatos e codecs
	av_register_all();

	//Procura o codec de video
	printf("Procurando codec...\n");
	codec = avcodec_find_encoder(CODEC_ID_H264);
	if (!codec) {
		fprintf(stderr, "Formato não encontrado.\n");
		return 1;
	}
	printf("Codec \"%s\" encontrado.\n", codec->long_name);

	//Aloca o codec
	//Isso foi encontrado em: http://stackoverflow.com/questions/15914012/encoding-a-screenshot-into-a-video-using-ffmpeg
	c = avcodec_alloc_context3(codec);
	c->bit_rate = 400000;
	c->width = 1024;			//A resolução tem que ser um número multiplo de 2
	c->height = 768;
	c->time_base.num = 1;				//Numerador da taxa de FPS
	c->time_base.num = 25;				//Denominador da taxa de FPS
	c->gop_size = 100;					//Emite 1 quadro inteiro a cada 100 quadros parciais
	c->max_b_frames = 1;				////NÃO SEI O QUE É ISSO
	c->keyint_min = 10;					//Tamanho mínimo do gop_size
	c->i_quant_factor = 0.71f;			////NÃO SEI O QUE É ISSO, mas tem a ver com "quantizer"
	c->b_frame_strategy = 20;			////NÃO SEI O QUE É ISSO
	c->qcompress = 0.6f;				////NÃO SEI O QUE É ISSO, mas tem a ver com "quantizer"
	c->qmin = 20;						////NÃO SEI O QUE É ISSO, mas tem a ver com "quantizer"
	c->qmax = 51;						////NÃO SEI O QUE É ISSO, mas tem a ver com "quantizer"
	c->max_qdiff = 4;					////NÃO SEI O QUE É ISSO, mas tem a ver com "quantizer"
	c->refs = 4;						//Número de quadros de referência (Não sei exatamente no que isso influencia)
	c->trellis = 1;						////NÃO SEI O QUE É ISSO, max tem a ver com "quantizer"
	c->pix_fmt = PIX_FMT_YUV420P;
	c->codec_id = CODEC_ID_H264;
	c->codec_type = AVMEDIA_TYPE_VIDEO;

	return 0;
}