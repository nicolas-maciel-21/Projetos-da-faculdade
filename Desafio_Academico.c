#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[51];
    char local[100];
    int pontuacao;
    char alinhamento[20];
    int forca, inteligencia, sabedoria, carisma;
    int vida, sanidade, energia;
    int capitulo;
    int estudou;
    int descansou;
    int bonus_dano;
} Personagem;

void limparTela() {
    system("cls || clear");
}

void pausa() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void grava(Personagem p) {
    FILE *f = fopen("save.dat", "wb");
    if (f) {
        fwrite(&p, sizeof(Personagem), 1, f);
        fclose(f);
        printf("Jogo salvo com sucesso!\n");
    } else {
        printf("Erro ao salvar jogo.\n");
    }
}

int le(Personagem *p) {
    FILE *f = fopen("save.dat", "rb");
    if (f) {
        fread(p, sizeof(Personagem), 1, f);
        fclose(f);
        return 1;
    }
    return 0;
}

void recorde(Personagem p) {
    FILE *f = fopen("ranking.txt", "a");
    if (f) {
        fprintf(f, "%s - %d pontos\n", p.nome, p.pontuacao);
        fclose(f);
    }
}

void ranking() {
    FILE *f = fopen("ranking.txt", "r");
    char linha[100];
    if (f) {
        printf("\n=== RANKING ===\n");
        while (fgets(linha, sizeof(linha), f)) {
            printf("%s", linha);
        }
        fclose(f);
    } else {
        printf("Nenhum ranking disponivel.\n");
    }
}

void listarIntegrantes() {
    printf("\nIntegrantes do grupo:\n");
    printf("- Nicolas Maciel\n");
}

void criar(Personagem *p) {
    limparTela();
    printf("=== Criacao do Personagem ===\n");
    printf("Digite o nome do personagem: ");
    fgets(p->nome, 51, stdin);
    p->nome[strcspn(p->nome, "\n")] = '\0';

    int pontos = 10;
    p->forca = p->inteligencia = p->sabedoria = p->carisma = 0;

    while (pontos > 0) {
        printf("\nPontos restantes: %d\n", pontos);
        printf("1. Forca (%d)\n2. Inteligencia (%d)\n3. Sabedoria (%d)\n4. Carisma (%d)\nEscolha um atributo: ", p->forca, p->inteligencia, p->sabedoria, p->carisma);
        int escolha;
        scanf("%d", &escolha);
        getchar();
        if (escolha >= 1 && escolha <= 4) {
            switch (escolha) {
                case 1: p->forca++; break;
                case 2: p->inteligencia++; break;
                case 3: p->sabedoria++; break;
                case 4: p->carisma++; break;
            }
            pontos--;
        } else {
            printf("Escolha invalida.\n");
        }
    }

    p->vida = 100;
    p->sanidade = 100;
    p->energia = 60;
    strcpy(p->alinhamento, "Neutro");
    strcpy(p->local, "Inicio da Jornada");
    p->pontuacao = 0;
    p->capitulo = 0;
    p->estudou = 0;
    p->descansou = 0;
    p->bonus_dano = 0;
    limparTela();
    printf("\n%s acabou de acordar. Como em qualquer outro dia, ele ja levanta pensativo sobre o que fazer no futuro. Ele lembra então que o resultado do SISU saiu.\n", p->nome);
    pausa();

    limparTela();
    printf("\nVoce passou! Sua mae acabou de entrar no quarto e ficou muito feliz assim que viu o resultado. Pode fazer sua matrícula.\n");
    printf("1. Realizar matricula\n2. Nao, eu quero mesmo e ser um rapper\nEscolha: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();

    if (escolha == 2) {
        limparTela();
        printf("\nSua mae fica enfurecida e te da um tapa na orelha. Sua unica opcao e fazer a matricula.\n");
        pausa();
    }
    
    limparTela();
    printf("\nVoce realizou a matricula com sucesso. A jornada comeca!\n");
    pausa();
}

void combate(Personagem *jogador, Personagem *inimigo) {
    limparTela();
    printf("Inimigo: %s diz: ", inimigo->nome);
    if (strcmp(inimigo->nome, "Circuitos digitais") == 0) printf("\"Faca a tabela!\"\n");
    else if (strcmp(inimigo->nome, "Carne moida do RU") == 0) printf("\"Bom apetite\"\n");
    else if (strcmp(inimigo->nome, "GA") == 0) printf("\"Vou te reduzir a forma canonica!\"\n");
    else if (strcmp(inimigo->nome, "MD") == 0) printf("\"Encare a incerteza e responda com razao\"\n");
    else if (strcmp(inimigo->nome, "PE") == 0) printf("\"Eu sou a base desse universo, voce nao pode me vencer\"\n");
    else if (strcmp(inimigo->nome, "Fim de periodo") == 0) printf("\"DESISTA!!!\"\n");

    while (jogador->vida > 0 && inimigo->vida > 0) {
        printf("\nSua Vida: %d | Sua Sanidade: %d | Sua Energia: %d | Vida do Inimigo: %d\n",
               jogador->vida, jogador->sanidade, jogador->energia, inimigo->vida);
        printf("1. Atacar\n2. Estudar (perde sanidade, aumenta dano)\n3. Descansar (recupera sanidade, reduz dano)\n4. Recuperar vida (usa 10 de energia e recupera 20 de vida)\nEscolha: ");
        int escolha;
        scanf("%d", &escolha);
        getchar();

       int dano = 5 + jogador->inteligencia * 2 + jogador->bonus_dano;

        if (escolha == 2) {
            jogador->sanidade -= 15;
            jogador->estudou++;
            jogador->bonus_dano += 3;  
            inimigo->vida -= dano;
            printf("Voce estudou e causou %d de dano.\n", dano);
        }
        else if (escolha == 3) {
            jogador->sanidade += 10;
            jogador->descansou++;
            jogador->bonus_dano -= 2; 
            if (jogador->bonus_dano < 0) jogador->bonus_dano = 0;
            inimigo->vida -= dano;
            printf("Voce descansou e causou %d de dano.\n", dano);
        }
         else if (escolha == 4) {
            if (jogador->energia >= 10) {
                jogador->energia -= 10;
                jogador->vida += 25;
                if (jogador->vida > 100) jogador->vida = 100;
                printf("Voce recuperou 25 de vida usando energia.\n");
            } else {
                printf("Energia insuficiente para recuperar vida!\n");
                continue;
            }
        }
        else if (escolha == 1) {
            inimigo->vida -= dano;
            printf("Voce causou %d de dano.\n", dano);
        }
        else {
            printf("Escolha invalida!\n");
            continue;
        }
        if (inimigo->vida > 0) {
            int dano_inimigo = 5;
            if (jogador->capitulo >= 2) {
             dano_inimigo += 5 * (jogador->capitulo - 2);
            }
            jogador->vida -= dano_inimigo;
            printf("O inimigo atacou e causou %d de dano.\n", dano_inimigo);
        }
    }

    if (jogador->sanidade < 30) {
        jogador->vida -= 10;
        printf("Sua sanidade esta baixa, voce perdeu 10 de vida.\n");
    }

    if (jogador->vida <= 0 || jogador->sanidade <= 0) {
        printf("\nVoce perdeu!\n");
        exit(0);
    } else {
        printf("\nVoce venceu!\n");
        jogador->pontuacao += 20;
    }
    pausa();
}


void capitulo1(Personagem *p);
void capitulo2(Personagem *p);
void capitulo3(Personagem *p);
void capitulo4(Personagem *p);
void capitulo5(Personagem *p);
void capitulo6(Personagem *p);
void final(Personagem *p);


void menu(Personagem *p) {
    while (1) {
        switch (p->capitulo) {
            case 0:
                capitulo1(p);
                break;
            case 1:
                capitulo2(p);
                break;
            case 2:
                capitulo3(p);
                break;
            case 3:
                capitulo4(p);
                break;
            case 4:
                capitulo5(p);
                break;
            case 5:
                capitulo6(p);
                break;
            default:
                final(p);
                return;
        }
    }
}

void capitulo1(Personagem *p) {
    limparTela();
    printf("=== CAPITULO 1: Circuitos Digitais ===\n");
    printf("Voce entra na primeira aula da faculdade: Circuitos Digitais.\n");
    printf("1. Tentar montar a tabela sozinho\n2. Perguntar ao professor\nEscolha: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();
    if (escolha == 1) {
        printf("Voce tenta e consegue montar. Forca de vontade aumenta sua pontuacao.\n");
        p->pontuacao += 10;
    } else {
        printf("Voce aprende com o professor. Inteligencia aumentada.\n");
        p->inteligencia++;
    }
    pausa();
    Personagem inimigo = {"Circuitos digitais", "", 0, "", 2, 1, 1, 1, 30, 0, 0};
    combate(p, &inimigo);
    p->capitulo++;
}

void capitulo2(Personagem *p) {
    limparTela();
    printf("=== CAPITULO 2: Carne moida do RU ===\n");
    printf("Voce precisa almocar, mas esta com medo da carne moida duvidosa do RU.\n");
    printf("1. Comer mesmo assim\n2. Ir embora e comer fora\nEscolha: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();
    if (escolha == 1) {
        printf("O sabor te deixa meio aborrecido, mas sua coragem e honrosa. Perde sanidade, aumenta a pontuacao.\n");
        p->sanidade -= 10;
        p->pontuacao += 5;
    } else {
        printf("E custoso e nada saudavel, mas quem pode te julgar? Perde pontos de vida, aumenta pontuacao.\n");
        p->vida -= 5;
        p->pontuacao += 10;
    }
    pausa();
    Personagem inimigo = {"Carne moida do RU", "", 0, "", 2, 1, 1, 1, 40, 0, 0};
    combate(p, &inimigo);
    p->capitulo++;
}

void capitulo3(Personagem *p) {
    limparTela();
    printf("=== CAPITULO 3: GA ===\n");
    printf("Voce chegou na temida aula de GA.\n");
    printf("1. Dormir\n2. Prestar atencao\nEscolha: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();
    if (escolha == 2) {
        printf("Parabens pelo esforco, voce sera recompensado.Aumenta inteligencia e pontuacao.\n");
        p->inteligencia++;
        p->pontuacao += 10;
    } else {
        printf("As vezes a mente precisa de um descanso. Aumenta a sanidade");
        p->sanidade += 5;
    }
    pausa();
    Personagem inimigo = {"GA", "", 0, "", 3, 2, 1, 2, 50, 0, 0};
    combate(p, &inimigo);
    p->capitulo++;
}

void capitulo4(Personagem *p) {
    limparTela();
    printf("=== CAPITULO 4: MD ===\n");
    printf("Voce precisa resolver problemas de MD.\n");
    printf("1. Tentar resolver sozinho\n2. Pegar resolucoes antigas\nEscolha: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();
    if (escolha == 1) {
        printf("Uau, quanto esforco!Voce e quase um monge. Aumenta inteligencia e sabedoria.\n");
        p->inteligencia++;
        p->sabedoria++;
    } else {
        printf("Um mero mortal. Pelo menos voce assume isso. Sanidade aumenta.\n");
        p->sanidade += 10;
    }
    pausa();
    Personagem inimigo = {"MD", "", 0, "", 3, 3, 2, 2, 55, 0, 0};
    combate(p, &inimigo);
    p->capitulo++;
}

void capitulo5(Personagem *p) {
    limparTela();
    printf("=== CAPITULO 5: PE ===\n");
    printf("Voce precisa entregar o trabalho de PE.\n");
    printf("1. Fazer sozinho\n2. Pedir ajuda\nEscolha: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();
    if (escolha == 1) {
        printf("Voce desistiu de viver faz tempo, sabemos disso. Aumenta inteligencia e pontuacao.\n");
        p->inteligencia++;
        p->pontuacao += 15;
    } else {
        printf("As vezes uma ajudinha cai bem, serve ate pra trabalhar soft skills. Carisma aumenta.\n");
        p->carisma++;
    }
    pausa();
    Personagem inimigo = {"PE", "", 0, "", 4, 3, 3, 2, 60, 0, 0};
    combate(p, &inimigo);
    p->capitulo++;
}

void capitulo6(Personagem *p) {
    limparTela();
    printf("=== CAPITULO FINAL: Fim de periodo ===\n");
    printf("Provas finais, projetos acumulados, pressao. Voce chegou ao fim do periodo.\n");
    printf("1. Estudar sem parar\n2. Fazer o possivel e descansar tambem\nEscolha: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();
    if (escolha == 1) {
        printf("Voce esta deixando sua humanidade de lado aos poucos, mas faz parte de cursar ccomp. Aumenta inteligencia e diminui sanidade.\n");
        p->inteligencia++;
        p->sanidade -= 15;
    } else {
        printf("Voce sabe que isso vai te causar ansiedade e talvez resultados ruins, mas pelo menos vai pensar nisso tendo dormido. Aumenta sanidade.\n");
        p->sanidade += 10;
    }
    pausa();
    Personagem inimigo = {"Fim de periodo", "", 0, "", 5, 4, 4, 3, 70, 0, 0};
    combate(p, &inimigo);
    p->capitulo++;
}

void final(Personagem *p) {
    limparTela();
    printf("=== FIM DO JOGO ===\n");

    int bonusCarisma = p->carisma * 2;
    int bonusSabedoria = p->sabedoria * 3;
    int pontuacaoFinal = p->pontuacao + bonusCarisma + bonusSabedoria;

    printf("Parabens, %s! Voce concluiu o periodo!\n", p->nome);
    printf("Pontuacao base: %d\n", p->pontuacao);
    printf("Bonus por carisma: +%d\n", bonusCarisma);
    printf("Bonus por sabedoria: +%d\n", bonusSabedoria);
    printf("Pontuacao final: %d\n", pontuacaoFinal);
    printf("\n--- Reflexao Final ---\n");
    if (p->carisma > p->sabedoria && p->carisma > p->inteligencia) {
        printf("Voce terminou o periodo fazendo amigos, apresentando trabalhos em grupo e sendo admirado por todos.\n");
        printf("O verdadeiro poder estava no jeito que voce cativava as pessoas.\n");
    } else if (p->sabedoria > p->carisma && p->sabedoria > p->inteligencia) {
        printf("Sua jornada foi marcada por escolhas bem pensadas e tranquilidade.\n");
        printf("Mesmo diante do caos, voce manteve a calma e aprendeu com tudo.\n");
    } else if (p->inteligencia > p->carisma && p->inteligencia > p->sabedoria) {
        printf("Voce devorou livros, venceu as provas mais dificeis e superou todos os desafios mentais.\n");
        printf("Um verdadeiro genio em ascensao.\n");
    } else {
        printf("Voce teve uma jornada equilibrada, usando um pouco de cada habilidade para vencer.\n");
        printf("Nem so de inteligencia se faz um vitorioso. Seu caminho foi completo.\n");
    }

    p->pontuacao = pontuacaoFinal;
    recorde(*p);

    printf("\nDeseja reiniciar? (1 - Sim / Outro - Nao): ");
    int opcao;
    scanf("%d", &opcao);
    getchar();
    if (opcao == 1) {
        criar(p); 
        p->capitulo = 0;
        menu(p);
    } else {
        exit(0);
    }
}


void inicio() {
    Personagem jogador;
    int opcao;
    while (1) {
        limparTela();
        printf("=== BEM-VINDO AO DESAFIO ACADEMICO ===\n");
        printf("1. Novo Jogo\n2. Continuar\n3. Ranking\n4. Integrantes do grupo\n5. Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                criar(&jogador);
                menu(&jogador);
                break;
            case 2:
                if (le(&jogador)) {
                    printf("Jogo carregado!\n");
                    pausa();
                    menu(&jogador);
                } else {
                    printf("Nenhum jogo salvo encontrado.\n");
                    pausa();
                }
                break;
            case 3:
                ranking();
                pausa();
                break;
            case 4:
                listarIntegrantes();
                pausa();
                break;
            case 5:
                exit(0);
            default:
                printf("Opcao invalida!\n");
                pausa();
        }
    }
}

int main() {
    inicio();
    return 0;
}

