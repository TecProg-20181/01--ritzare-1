#include <stdio.h>

typedef struct _pixel {
  unsigned short int r;
  unsigned short int g;
  unsigned short int b;
} Pixel;

typedef struct _image {
  // [width][height][rgb]
  // 0 -> r
  // 1 -> g
  // 2 -> b
  Pixel pixel[512][512];
  unsigned int w;
  unsigned int h;
} Image;


int max(int a, int b) {
  if (a > b)
    return a;
return b;
}
int min(int a, int b) {
  if (a > b)
    return b;
return a;
}


Image gray(Image img) {


  for (unsigned int i = 0; i < img.h; ++i) {
    for (unsigned int j = 0; j < img.w; ++j) {
      int media = img.pixel[i][j].r +
      img.pixel[i][j].g +
      img.pixel[i][j].b;
      media /= 3;
      img.pixel[i][j].r = media;
      img.pixel[i][j].g = media;
      img.pixel[i][j].b = media;
    }
  }

  return img;
}

Image sepia(Image img) {
  for (unsigned int x = 0; x < img.h; ++x) {
    for (unsigned int j = 0; j < img.w; ++j) {
      Pixel pixel;
      pixel.r = img.pixel[x][j].r;
      pixel.g = img.pixel[x][j].g;
      pixel.b = img.pixel[x][j].b;

      int p =  pixel.r * .393 + pixel.g * .769 + pixel.b * .189;
      int menor_r = min(255 ,  p);
      img.pixel[x][j].r = menor_r;

      p =  pixel.r * .349 + pixel.g * .686 + pixel.b * .168;
      menor_r = min(255 ,  p) ;
      img.pixel[x][j].g = menor_r;

      p =  pixel.r * .272 + pixel.g * .534 + pixel.b * .131;
      menor_r = min(255 ,  p) ;
      img.pixel[x][j].b = menor_r;
    }
  }
  return img;
}


Image blur(Image img) {
  int T = 0;
  scanf("%d", &T);
  for (unsigned int i = 0; i < img.h; ++i) {
    for (unsigned int j = 0; j < img.w; ++j) {
      Pixel media = {0, 0, 0};

      int menor_h = min(img.h - 1 , i + T/2) ;
      int min_w = min(img.w - 1 , j + T/2) ;
      for(int x = max(0 , i - T/2); x <= menor_h; ++x) {
        for(int y = max(0 , j - T/2); y <= min_w; ++y) {
          media.r += img.pixel[x][y].r;
          media.g += img.pixel[x][y].g;
          media.b += img.pixel[x][y].b;
        }
      }

      media.r /= T * T;
      media.g /= T * T;
      media.b /= T * T;

      img.pixel[i][j].r = media.r;
      img.pixel[i][j].g = media.g;
      img.pixel[i][j].b = media.b;
    }
  }
  return img;
}

Image rotationright(Image img) {
  Image rotacionada;

  rotacionada.w = img.h;
  rotacionada.h = img.w;

  for (unsigned int i = 0, y = 0; i < rotacionada.h; ++i, ++y) {
    for (int j = rotacionada.w - 1, x = 0; j >= 0; --j, ++x) {
      rotacionada.pixel[i][j].r = img.pixel[x][y].r;
      rotacionada.pixel[i][j].g = img.pixel[x][y].g;
      rotacionada.pixel[i][j].b = img.pixel[x][y].b;
    }
  }

  return rotacionada;
}

Image rot(Image img) {
  int quantas_vezes = 0;;
  scanf("%d", &quantas_vezes);
  quantas_vezes %= 4;
  for (int j = 0; j < quantas_vezes; ++j) {
    img = rotationright(img);
  }
  return img;
}



Image horizontal(Image img) {
  int horizontal = 0;
  scanf("%d", &horizontal);

  int w = img.w, h = img.h;

  if (horizontal == 1)
    w /= 2;
  else
    h /= 2;

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      int x = i, y = j;

      if (horizontal == 1)
        y = img.w - 1 - j;
      else
        x = img.h - 1 - i;

      Pixel aux1;
      aux1.r = img.pixel[i][j].r;
      aux1.g = img.pixel[i][j].g;
      aux1.b = img.pixel[i][j].b;

      img.pixel[i][j].r = img.pixel[x][y].r;
      img.pixel[i][j].g = img.pixel[x][y].g;
      img.pixel[i][j].b = img.pixel[x][y].b;

      img.pixel[x][y].r = aux1.r;
      img.pixel[x][y].g = aux1.g;
      img.pixel[x][y].b = aux1.b;
    }
  }
  return img;
}
Image invert(Image img) {
  for (unsigned int i = 0; i < img.h; ++i) {
    for (unsigned int j = 0; j < img.w; ++j) {
      img.pixel[i][j].r = 255 - img.pixel[i][j].r;
      img.pixel[i][j].g = 255 - img.pixel[i][j].g;
      img.pixel[i][j].b = 255 - img.pixel[i][j].b;
    }
  }
  return img;
}
Image cut(Image img) {
  Image cortada;
  int x, y;
  scanf("%d %d", &x, &y);
  int w, h;
  scanf("%d %d", &w, &h);
  cortada.w = w;
  cortada.h = h;

  for(int i = 0; i < h; ++i) {
    for(int j = 0; j < w; ++j) {
      cortada.pixel[i][j].r = img.pixel[i + y][j + x].r;
      cortada.pixel[i][j].g = img.pixel[i + y][j + x].g;
      cortada.pixel[i][j].b = img.pixel[i + y][j + x].b;
    }
  }

  return cortada;
}


Image read(Image img) {

  char p3[4];
  scanf("%s", p3);

  int max_color;
  scanf("%u %u %d", &img.w, &img.h, &max_color);


  for (unsigned int i = 0; i < img.h; ++i) {
    for (unsigned int j = 0; j < img.w; ++j) {
      scanf("%hu %hu %hu", &img.pixel[i][j].r,
      &img.pixel[i][j].g,
      &img.pixel[i][j].b);

    }
  }
  return img;
}








void print(Image img) {

  printf("P3\n");

  printf("%u %u\n255\n", img.w, img.h);


  for (unsigned int i = 0; i < img.h; ++i) {
    for (unsigned int j = 0; j < img.w; ++j) {
      printf("%hu %hu %hu ", img.pixel[i][j].r,
      img.pixel[i][j].g,
      img.pixel[i][j].b);

    }
    printf("\n");
  }
}

int main() {
  Image img;

  img = read(img);

  int n_opcoes;
  scanf("%d", &n_opcoes);

  for(int i = 0; i < n_opcoes; ++i) {
    int opcao;
    scanf("%d", &opcao);

    switch(opcao) {
      case 1: { // Escala de Cinza
        img = gray(img);
        break;
      }
      case 2: { // Filtro Sepia
        img = sepia(img);
        break;
      }
      case 3: { // Blur

        img = blur(img);
        break;
      }
      case 4: { // Rotacao
        img = rot(img);
        break;
      }
      case 5: { // Espelhamento
        img = horizontal(img);
        break;
      }
      case 6: { // Inversao de Cores
        img =  invert(img);
        break;
      }
      case 7: { // Cortar Imagem
        img = cut(img);
        break;
      }
    }

  }
  print(img);
  return 0;
}
