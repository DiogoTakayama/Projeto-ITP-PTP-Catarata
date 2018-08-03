# Projeto-ITP-PTP-Catarata
Projeto Para Tratamento de imagens na linguagem C
O​ ​Embasamento​ ​teórico​ ​do​ ​Projeto
Nesse projeto você deve fazer um programa em C para analisar 4 imagens (duas
com catarata e duas sem catarata) e emitir o diagnóstico final de cada. Para isso é preciso
realizar algumas etapas:

1. Transformação​ ​da​ ​imagem​ ​colorida​ ​para​ ​tons​ ​de​ ​cinza
Para converter qualquer cor em seu nível aproximado de cinza, deve-se primeiro
obter suas primitivas vermelho, verde e azul (da escala RedGreenBlue). Adiciona-se
então 30% do vermelho mais 59% do verde mais 11% do azul, independente da
escala utilizada (0.0 a 1.0, 0 a 255, 0% a 100%.) O nível resultante é o valor de cinza
desejado. Tais porcentagens estão relacionadas à própria sensibilidade visual do
olho humano convencional para as cores primárias.
2. Segmentação​ ​da​ ​imagem

A filtragem ​é um procedimento usual ao realizar o tratamento de uma imagem,
antes de que um determinado processamento possa ser feito. De uma forma geral a
filtragem de imagens é implementada através de uma multiplicação especial entre
duas matrizes (operação também chamada de convolução).

2.1 filtro gaussiano

Realce de Arestas ​é um processo de realce de arestas na imagem. Esse processo
recebe como entrada uma imagem e produz como saída outra imagem, porém
contendo apenas os contornos da imagem original, em preto e branco. Para muitos
procedimentos que precisam da detecção de figuras geométricas, como círculos, no
nosso caso, é necessário o uso de imagens que contenham apenas os contornos
das figuras na imagem ao invés dos valores de todos os pixels em RGB. Para tal é
necessário realizar uma série de procedimentos a fim de garantir a detecção dos
contornos com melhor qualidade (detector de arestas Canny):
a. Transformação da imagem para escalas de cinza
b. Aplicação de um filtro gaussiano
c. Filtragem com sobel
d. Cálculo das magnitudes em x e y, e cálculo das angulações das arestas
e. Atenuação/remoção dos valores que não são arestas
i. Processamento de vizinhança na direção do gradiente
ii. Remoção de valores através de duplo threshold

A Binarização é um tipo de processamento que se baseia na diferença dos níveis
de cinza que compõe diferentes objetos de uma imagem. A partir de um limiar
estabelecido de acordo com as características dos objetos que se quer isolar, a
imagem pode ser segmentada em dois grupos: o grupo de pixels com níveis de
cinza abaixo do limiar e o grupo de pixels com níveis de cinza acima do limiar. Em
uma imagem limiarizada, atribui-se um valor fixo para todos os pixels de mesmo
grupo. No nosso caso, aplicaremos um procedimento de binarização na imagem
gerada a partir do realce de arestas. A imagem resultante após o processo de realce
de arestas ainda contém valores de pixel em tons de cinza, variando entre 0 e 255
dependendo do quão “forte” é a aresta em questão. O procedimento de binarização
irá transformar essa imagem em uma imagem binária (com valores de 0 e 1, ou
valores mínimos e máximos), onde os valores máximos representarão pixels que,
com certeza, estão em alguma aresta da imagem, enquanto os valores mínimos
representarão pixels que não estão em aresta alguma e, portanto, devem ser
desconsiderados.

A Transformada de Hough ​é uma técnica matemática que realiza a detecção de
formas geométricas em imagens digitais. Em sua forma original a transformada de
Hough foi elaborada por Paul Hough em 1962. Sua primeira concepção estava
baseada na localização de retas. Posteriormente, a transformada de Hough foi
estendida para possibilitar a localização de outras formas geométricas que possam
ser parametrizadas, tais como círculos e elipses. A transformação de Hough para
detecção de círculos processa a imagem dada como entrada e produz como saída
uma representação em um espaço de quatro dimensões, contendo valores possíveis
de todos os centros de círculos com determinado raio que podem interseccionar um
dado pixel da imagem. O procedimento para produzir a representação no espaço de
Hough para uma imagem é a seguinte:
a. Transforme a imagem em uma representação de arestas
b. Processe todos os pixels da imagem de arestas de acordo com o algoritmo
abaixo:

para cada pixel(x,y) que pertence a uma aresta
// os raios possíveis devem ser conhecidos, é necessário fazer
// ajustes manuais nessa parte para detecção de círculos
// com raios maiores que rmax pixels ou menores que rmin pixels
para cada raio r = rmin à r = rmax
para cada theta t = 0 à 360 // valores padrão
a = x – r * cos(t * PI / 180); //coordenada a do centro
b = y – r * sin(t * PI / 180); //coordenada b do centro
A[a,b,r] +=1; //espaço de Hugh
end
end
end

c. Ao fim do algoritmo a matriz A[a,b,r] contém todos os centros (a,b) para todos
os círculos de raios (r), no intervalo de raios considerados, que
interseccionam todos os pixels que pertencem às arestas da imagem. Assim,
se uma imagem contém apenas UM círculo, com centro (Ac, Bc) e raio Rc
(com rmin<=Rc<=rmax); espera-se que o valor de A[Ac,Bc,Rc] seja maior do
que outros valores da matriz A, indicando assim a presença do círculo na
posição e raios especificados na matriz.

d. Caso a imagem contenha mais de um círculo, é necessário encontrar mais
de um máximo na matriz A, por exemplo, podemos, ao invés de procurar
apenas pelo maior valor de A, buscar pelos n maiores valores, que
representam as n circunferências detectadas pelo algoritmo.

COMPILAÇÃO

Para compilar o projeto, é necessário somente inserir o comando 'make' enquanto estiver no diretório do projeto, ou inserir os seguintes comandos:
'gcc -o a.out main.c io.c operacoes.c -lm'

para carregar a imagem por parametro:
./a.out -i <input-image>.ppm

