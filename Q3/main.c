
#include "./src/Q3.h"

int buscarPrimeiroInicio(Memoria *raiz)
{
    int resultado = -1;

    if (raiz != NULL)
    {
        Memoria *atual = raiz;

        while (atual->left != NULL)
            atual = atual->left;
        resultado = atual->info1->inicio;
    }

    return (resultado);
}

int buscarUltimoInicio(Memoria *raiz)
{
    int resultado = -1;

    if (raiz != NULL)
    {
        Memoria *atual = raiz;
        while (atual->right != NULL)
            atual = atual->right;

        if (atual->numKeys == 2 && atual->info2 != NULL)
            resultado = atual->info2->inicio;
        else
            resultado = atual->info1->inicio;
    }

    return (resultado);
}

void Menu()
{
    printf("\n===============================================================\n");
    printf("                          MENU PRINCIPAL                      \n");
    printf("===============================================================\n");
    printf("  [1] Ocupar Nós Livres\n");
    printf("  [2] Desocupar Nós\n");
    printf("  [3] Exibir Alocação de Memória\n");
    printf("  [4] Sair\n");
    printf("===============================================================\n");
    printf("Escolha uma opção (1-4): ");
}


int main()
{
    Memoria *raiz = NULL;
    Info *novaInfo;
    Info promove;
    int inicio = 0, fim = 0, status = 2, quantEspaco, menuControl = 0, block, espaco, inicio2 = 0, removeinicio;
    char opc;

    srand(time(NULL));

    printf("===============================================================\n");
    printf("          Bem-vindo ao Gerenciador de Memória Dinâmica          \n");
    printf("===============================================================\n");
    printf("Indique o tamanho total da memória (em unidades): ");
    scanf("%d", &block);

    do
    {
        printf("\nInforme o valor de fim para alocação de memória:\n");
        printf("Valor de Início = 0\n");
        printf("Informe o valor de fim: ");
        scanf("%d", &fim);
    } while (inicio < 0 || fim > block || fim < inicio);

    do
    {
        printf("\nO bloco de memória está livre ou ocupado? (L - Livre / O - Ocupado): ");
        scanf(" %c", &opc);

        switch (opc)
        {
        case 'L':
            status = LIVRE;
            break;
        case 'O':
            status = OCUPADO;
            break;
        default:
            printf("\nOpção inválida! Por favor, escolha entre 'L' para Livre ou 'O' para Ocupado.\n");
        }

    } while (status != LIVRE && status != OCUPADO);

    novaInfo = criarInfo(inicio, fim, status);
    insereArv23(&raiz, novaInfo, &promove, NULL);
    inicio = fim + 1;

    while (fim != block)
    {
        printf("\nInforme o valor final da memória (entre %d e %d): ", inicio, block);
        scanf("%d", &fim);

        if (fim >= inicio && fim <= block)
        {
            if (status == LIVRE)
                status = OCUPADO;
            else
                status = LIVRE;

            novaInfo = criarInfo(inicio, fim, status);
            insereArv23(&raiz, novaInfo, &promove, NULL);
            inicio = fim + 1;
        }
        else
            printf("\nValor de fim inválido. Informe um valor entre %d e %d.\n", inicio, block);
    }
    do
    {
        Menu();
        scanf("%d", &menuControl);

        switch (menuControl)
        {
        case 1:
            printf("\nInforme o espaço necessário para alocação: ");
            scanf("%d", &quantEspaco);
            espaco = alocaEspaco(&raiz, quantEspaco, &inicio2);
            if (espaco == quantEspaco)
            {
                if (buscarPrimeiroInicio(raiz) == inicio2)
                {
                    
                    mergeNosInicio(&raiz, &removeinicio);
                    removeMemoria(&raiz, removeinicio);
                    printf("Compactação realizada no início da memória.\n");
                }
                else if (buscarUltimoInicio(raiz) == inicio2)
                {
                    mergeNosFim(&raiz, &removeinicio);
                    removeMemoria(&raiz, removeinicio);
                    printf("Compactação realizada no fim da memória.\n");
                }
                else
                {
                    int aux1, aux2;
                    mergeNosMeio(&raiz, &aux1, &aux2);
                    printf("%d %d\n", aux1, aux2);

                    removeMemoria(&raiz, aux1);
                    removeMemoria(&raiz, aux2);
                    printf("Compactação realizada no meio da memória.\n");
                }
            }
            break;

        case 2:
            printf("\nInforme o início da memória a ser desocupada: ");
            scanf("%d", &inicio);
            printf("Informe o fim da memória a ser desocupada: ");
            scanf("%d", &fim);
            freeEspaco(raiz, inicio, fim);
            if (buscarPrimeiroInicio(raiz) == inicio)
            {
                int removeinicio;
                mergeNosInicio(&raiz, &removeinicio);
                removeMemoria(&raiz, removeinicio);
                printf("Compactação realizada no início da memória.\n");
            }
            else if (buscarUltimoInicio(raiz) == inicio)
            {
                mergeNosFim(&raiz, &removeinicio);
                removeMemoria(&raiz, removeinicio);
                printf("Compactação realizada no fim da memória.\n");
            }
            else
            {
                int aux1, aux2;
                mergeNosMeio(&raiz, &aux1, &aux2);
                removeMemoria(&raiz, aux1);
                removeMemoria(&raiz, aux2);
                printf("Compactação realizada no meio da memória.\n");
            }
            break;

        case 3:
            printf("\nExibindo alocação de memória...\n");
            exibirInfos(raiz);
            break;

        case 4:
            printf("\nSaindo da aplicação...\n");
            break;

        default:
            printf("\nOpção inválida! Por favor, escolha uma opção entre 1 e 6.\n");
            break;
        }
    } while (menuControl != 4);

    return 0;
}