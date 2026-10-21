# CRONOGRAMA TCC (≈13h30 no total)

**Regras:** pausa de 10 min a cada 50 min. Travou 20 min num passo? Anote o problema, pule para o próximo. Fim de cada bloco: PDF compilando.
**Prazo de entrega:** ____/____

- [x] Diminuir margem (já feito no `USPSC-TCC-NINA.tex`: 2 cm laterais, 2,5 cm em cima, 2 cm embaixo, `oneside`)

---

## BLOCO 0: antes de tudo (5 min)

- [ ] (2 min) Mandar mensagem à orientadora: "As 20 páginas contam capa, resumo, listas e sumário, ou só o texto? Posso tirar as 2 páginas em branco do modelo? O apêndice conta?"
- [ ] (3 min) Preâmbulo do `USPSC-TCC-NINA.tex`: colar depois do `\newcommand{\lgray}...`:
  `\newcommand{\todo}[1]{\textcolor{red}{[PENDENTE: #1]}}`
  (Na entrega, trocar por `\newcommand{\todo}[1]{}` para sumirem todos.)

---

## BLOCO 1: compilar e limpar (≈1h45)

### 1.1 Bibliografia (≈20 min)
- [ ] (2 min) Apagar o `bib.bib` antigo. Confirmar que `USPSC-bib/bib.bib` é o novo (o de `bib_copy`).
- [ ] (3 min) `USPSC-TCC-NINA.tex`: trocar `\bibliography{USPSC-bib/bib.bib}` por `\bibliography{USPSC-bib/bib}` (sem `.bib`).
- [ ] (3 min) `bib.bib`, entrada `arenales`: trocar o autor por
  `author = {Arenales, Marcos and Armentano, Vin{\'i}cius and Morabito, Reinaldo and Yanasse, Horacio},`
- [ ] (2 min) Mesma entrada: apagar o comentário `% <- ADICIONE...`. Manter `address` só se confirmar a cidade na ficha do livro; senão, apagar a linha.
- [ ] (3 min) Renomear a chave `key` para `mundim2017` no `bib.bib`.
- [ ] (3 min) Ctrl+Shift+H: trocar `\cite{key}` por `\cite{mundim2017}` em todos os arquivos.
- [ ] (4 min) Conferir no artigo o 3º autor de `mundim2017` (acho que é "de Queiroz, Thiago Alves"). Corrigir.

### 1.2 Limpar os capítulos (≈30 min)
- [ ] (5 min) **ANTES de apagar:** abrir o Cap2, copiar para o `notas.md` os exemplos de tabela `\IBGEtab` (linhas ~21 a 60) e de figura (linhas ~84 a 100). Você vai precisar do formato depois.
- [ ] (5 min) Cap2: apagar da linha 9 até a linha anterior a `\section{Formulação de um problema de corte de itens irregulares}` (linha 184). Depois, apagar as linhas 1 a 7. **Manter** a linha 8: `\chapter{Desenvolvimento}\label{cap_exemplos}`.
- [ ] (5 min) Cap1: apagar os comentários do topo e a frase "Parte inicial do texto, que contém...". Manter `\chapter[Introdução]{Introdução}`.
- [ ] (3 min) Cap3: apagar os comentários do topo e a frase "Apresentar as conclusões...". Manter `\chapter{Conclusão}` e a `\section{Considerações Finais}`.
- [ ] (10 min, opcional) Cap2: apagar as linhas comentadas que sobraram. Ctrl+H com regex ligado: buscar `^\s*%.*\n`, deixar a substituição vazia. Antes de aplicar, olhe as ocorrências: elas incluem `% item 0 copia 0` dentro dos tikz (inofensivo) e `%escala`/`%tempo` (guarde se quiser).
- [ ] (2 min) Procurar `textcolor{red` e trocar cada um por `\todo{...}` (ou deixar para depois).

### 1.3 Tabelas (≈15 min)
Ctrl+F `adjustwidth`: são 8 ocorrências (4 abrindo, 4 fechando).
- [ ] (3 min) Tabela 1 (`tab:t1`): `\begin{adjustwidth}{-2cm}{-2.5 cm}\centering\begin{threeparttable}[!htb]\centering` vira `\begin{threeparttable}\centering`. E `\end{threeparttable}\end{adjustwidth}` vira `\end{threeparttable}`.
- [ ] (3 min) Tabela 2 (`tab:t2`): mesma troca.
- [ ] (3 min) Tabela 3 (`tab:t3`): mesma troca.
- [ ] (3 min) Tabela 4 (`tab:t4`): mesma troca.
- [ ] (3 min) Ctrl+F `[!htb]`: confirmar que não sobrou nenhum depois de `threeparttable`.

### 1.4 Arquivo principal `USPSC-TCC-NINA.tex` (≈15 min)
- [ ] (2 min) Apagar `\include{USPSC-TA-PreTextual/USPSC-Errata}`.
- [ ] (2 min) Apagar `\include{...USPSC-Dedicatoria}` e `\include{...USPSC-Epigrafe}`.
- [ ] (2 min) Apagar `\include{...USPSC-AbreviaturasSiglas}` e `\include{...USPSC-Simbolos}`.
- [ ] (3 min) Apagar as 3 linhas da lista de quadros: `\pdfbookmark[0]{\listofquadroname}{loq}`, `\listofquadro*` e o `\cleardoublepage` que vem logo depois.
- [ ] (2 min) Apagar as linhas `\usepackage{chemfig}`, `\usepackage{chemmacros}` e `\usepackage{lipsum}`.
- [ ] (2 min) *(só depois de a orientadora responder)* Apagar os 2 `\includepdf{...PaginaEmBranco.pdf}`.
- [ ] (2 min) Decidir sobre `\include{...USPSC-Agradecimentos}`: manter se for escrever agradecimentos, apagar se não.

### 1.5 Compilar (≈20 min)
- [ ] (5 min) Compilar com latexmk (rodar duas vezes se pedir).
- [ ] (5 min) No painel de saída/log, procurar a primeira linha com `!` ou `Error`. Corrigir só ela, recompilar. Repetir.
- [ ] (5 min) Quando zerar os erros, procurar "undefined" no log. Citações ou referências com `?` ainda podem sobrar nesta etapa; anote.
- [ ] (3 min) Anotar o número de páginas atual: ____
- [ ] (2 min) Copiar a pasta inteira como backup (`TCC_backup_bloco1`).

---

## BLOCO 2: pré-textual e referências (≈1h50)

### 2.1 Conferir capa e folha de rosto (≈10 min)
- [ ] (5 min) Abrir o PDF: título, seu nome, "Orientadora: Profa. Dra. Marina Andretta" e ano 2026 corretos na capa e na folha de rosto.
- [ ] (5 min) Em `USPSC-TCC-pre-textual-ICMC.tex`, preencher o título em inglês (`\titleabstract` e `\tituloadic`). Deixar `\cutter{ }` vazio por enquanto.

### 2.2 Resumo e Abstract (≈40 min)
Arquivos: `USPSC-TA-PreTextual/USPSC-Resumo.tex` e `USPSC-Abstract.tex`.
- [ ] (15 min) Escrever 5 frases, uma para cada item: problema (corte de itens irregulares em faixa), métodos (NFP/IFP, *Bottom-Left* com 12 ordenações, BRKGA), experimentos (29 instâncias), resultados principais (BL31 melhor em 12/29, BRKGA melhor em quase todas, custo ~1500× maior), conclusão.
- [ ] (5 min) Conferir se tem entre 150 e 250 palavras.
- [ ] (3 min) Preencher as palavras-chave (no formato do arquivo): otimização; corte e empacotamento; *No-Fit Polygon*; *Bottom-Left*; BRKGA.
- [ ] (15 min) Fazer a versão em inglês no Abstract, com *keywords*.
- [ ] (2 min) Compilar e olhar as 2 páginas no PDF.

### 2.3 Referências para o `.bib` (≈1h)
Para cada uma: buscar no Google Acadêmico, "Citar", "BibTeX", colar no `bib.bib`, trocar `;` por `and` e trocar a chave pela indicada. Conferir ano e acentos (`{\'e}`).
- [ ] (5 min) `dyckhoff1990`: Dyckhoff (1990), EJOR 44, tipologia de corte e empacotamento.
- [ ] (5 min) `wascher2007`: Wäscher, Haußner e Schumann (2007), EJOR 183.
- [ ] (5 min) `garey1979`: Garey e Johnson (1979), *Computers and Intractability*.
- [ ] (5 min) `baker1980`: Baker, Coffman e Rivest (1980), SIAM J. Comput. 9.
- [ ] (5 min) `albano1980`: Albano e Sapuppo (1980), IEEE Trans. SMC 10.
- [ ] (5 min) `dowsland1998`: Dowsland, Dowsland e Bennell (1998), JORS 49.
- [ ] (5 min) `burke2006`: Burke, Hellier, Kendall e Whitwell (2006), Operations Research 54.
- [ ] (5 min) `bean1994`: Bean (1994), ORSA J. Computing 6.
- [ ] (5 min) `goncalves2011`: Gonçalves e Resende (2011), J. Heuristics 17 (BRKGA).
- [ ] (5 min) `goncalves2013`: Gonçalves e Resende (2013), IJPE 145 (BRKGA para *bin packing*).
- [ ] (5 min) `art1966`: Art (1966), IBM Cambridge Scientific Center (NFP). Provavelmente `@techreport`, preencher à mão.
- [ ] (5 min) `esicup`: página do ESICUP como fonte das instâncias (`@misc` com `url` e `urlaccessdate`).
- [ ] (opcional, 5 min) `leao2020`: Leão et al. (2020), EJOR 282, revisão de modelos para empacotamento irregular.
- [ ] (3 min) Compilar e checar se o `.bbl` gerou sem erro.

---

## BLOCO 3: Introdução (≈2h)

Rascunhos A e B estão na minha resposta de revisão (seção 7). **As chaves lá são de exemplo: `bennell2009` = `irregular` e `bennell2008` = `geometry` no seu `.bib`.**

### 3.1 Parágrafos com referências (≈1h20)
- [ ] (5 min) Abrir `USPSC-Cap1-Introducao.tex` e o rascunho A lado a lado.
- [ ] (10 min) Colar o parágrafo 1 do rascunho A. Trocar `\cite{bennell2009}` por `\cite{irregular}` e `\cite{bennell2008}` por `\cite{geometry}`. Conferir `dyckhoff1990` e `wascher2007`.
- [ ] (10 min) Colar o parágrafo 2. Conferir cada chave: `garey1979`, `baker1980`, `albano1980`, `dowsland1998`, `goncalves2011`, `bean1994`, `goncalves2013`, `art1966`, `burke2006`.
- [ ] (10 min) Colar o parágrafo 3 (objetivo do trabalho). Trocar `\cite{esicup}` se o nome da chave for outro.
- [ ] (10 min, opcional) Adicionar uma frase citando `\cite{mundim2017}` e `\cite{containers}` (BRKGA e heurística geral para *nesting*, da sua orientadora).
- [ ] (10 min) Apagar os 3 parágrafos antigos que ficaram redundantes e o `\textcolor{red}{adicionar referências...}`.
- [ ] (10 min) Conferir o parágrafo final de organização do texto ("Na Seção~\ref{...}"). Manter "Seção", pois `Desenvolvimento` é um capítulo com seções.
- [ ] (5 min) Compilar e procurar `?` nas citações da Introdução.

### 3.2 Parágrafo da graduação (≈35 min)
- [ ] (10 min) No papel: listar 3 disciplinas que ajudaram de verdade na pesquisa e **por quê** (1 linha cada).
- [ ] (10 min) No papel: listar 1 ou 2 coisas que faltaram ou foram aprendidas por conta própria (geometria computacional, meta-heurísticas...).
- [ ] (10 min) Colar o rascunho B no fim da Introdução e substituir os colchetes pela sua lista.
- [ ] (5 min) Ler em voz alta e cortar o que estiver forçado.

---

## BLOCO 4: correções de conteúdo (≈3h30)

### 4.1 Frase invertida (5 min)
- [ ] (5 min) Cap2, Experimentos da BL: Ctrl+F `poly5A`. Corrigir: `poly1A` (razão 0,715) é a **maior** diferença e `poly5A` (razão 0,895) é a **menor**.

### 4.2 Ortografia e escrita (≈35 min)
Use Ctrl+Shift+F para achar cada trecho.
- [ ] (2 min) "problemas otimização" → "problemas **de** otimização" (se ainda estiver, depois da Introdução reescrita)
- [ ] (2 min) "trançando o caminho" → "**traçando**"
- [ ] (2 min) "decompô-lo ele em" → "decompô-lo em"
- [ ] (3 min) "é imprescindível estar atento se na alocação final não haja" → "é imprescindível **verificar que**, na alocação final, **não há**"
- [ ] (2 min) "utilizadas criar uma nova população" → "utilizadas **para** criar"
- [ ] (2 min) Legenda da `fig:f15`: "e e sua alocação" → "e sua alocação"
- [ ] (2 min) "os experimentos foram feitas" → "feitos"
- [ ] (2 min) "os resultado de cada execução" → "resultados"; "o comprimento final obtida" → "obtido"
- [ ] (2 min) "tem" → "**têm**" (procurar "indivíduos tem" e "I−4 tem")
- [ ] (2 min) "dois viés" → "dois **vieses**" (Cap2 e Cap3)
- [ ] (8 min) Números com vírgula em modo matemático: Ctrl+F `$0,`, `$b = 0,` etc. Trocar `$0,895$` por `$0{,}895$` (evita o espaço depois da vírgula).
- [ ] (5 min) Subfiguras com `\caption{}` vazio (`f15a`, `f15b`, `f16a`, `f16b`): preencher ou remover o `\caption`.
- [ ] (5 min) Padronizar maiúsculas: "Instância", "Tabela", "Seção" (sempre igual em todo o texto).

### 4.3 Tabelas 3 e 4 (≈50 min)
- [ ] (15 min) Abrir o arquivo de saída do seu programa e conferir os 5 valores divergentes entre as Tabelas 3 e 4: `poly1A` tempo (19,08 vs 19.07), `poly2A` BRKGA 0,5 (31,90 vs 31.94), `poly3b` (691,01 vs 691.00), `poly4b` (1490,48 vs 1490.47), `poly5b` (2847,81 vs 2847.80).
- [ ] (5 min) Corrigir o valor errado em cada tabela. Conferir se o destaque (célula cinza) do `poly2A` continua certo.
- [ ] (10 min) Tabela 4: selecione as linhas da tabela, abra o Ctrl+H, ative "Find in selection" e troque `.` por `,` nos números.
- [ ] (2 min) Tabela 4: trocar "bias" por "viés".
- [ ] (5 min) Decidir sobre a Tabela 3: apagar (a Tabela 4 já tem as duas colunas de BRKGA) ou mover para o apêndice. Marcar a decisão: ________
- [ ] (10 min) Ajustar o texto que referencia `tab:t3`.

### 4.4 Coerência (≈1h45)
- [ ] (10 min) Parágrafo que diz que o BRKGA foi melhor em todas: acrescentar que 4 soluções da BL entram na população inicial e a elite é mantida, então ele não pode ser pior que elas (rascunho D, 1ª frase).
- [ ] (10 min) Frase "1500 vezes": explicar a conta (razão média dos tempos). Calcule também o número de chamadas à BL com **os seus** parâmetros: população inicial + (gerações × indivíduos novos por geração). **Não copie o "820" do rascunho D sem conferir.**
- [ ] (15 min) Conclusão sobre viés 0,7 vs 0,5: acrescentar que foi uma execução por instância e a semente, e tratar como indício. Listar a limitação.
- [ ] (10 min) Algoritmo da BL, passo 2.d: dizer que cada interseção calculada precisa ser **validada** (fora de todos os NFPs e dentro do IFP).
- [ ] (15 min) Notação repetida: `M` (polígono, melhor ponto, nº de mutantes) e `C` (comprimento, nº de cruzamentos). Escolher símbolos novos para a seção do BRKGA (sugestão: população `p`, elite `p_e`, mutantes `p_m`, viés `\rho_e`, gerações `G`) e trocar no texto.
- [ ] (10 min) Considerações finais, "soluções boas e ruins": substituir por números (intervalo das razões; `BL_{31}` melhor em 12 de 29; `BL_{21}`).
- [ ] (10 min) Frase "Quando comparamos somente BL31, BL21, BL52 e BL11...": dar as contagens ou apagar.
- [ ] (10 min) Definir otimização e meta-heurística formalmente em 1 frase cada (se a Introdução nova não cobriu).
- [ ] (15 min) Colar o rascunho D (limitações) na Seção de comparação, ajustando os números aos seus parâmetros.
- [ ] (30 min, opcional) Fundamentação do `main.tex` (rascunho C): colar (10), adaptar notação (10), acrescentar a fórmula do IFP com α_D, β_D, γ_D do `main.tex` (10).

---

## BLOCO 5: apêndice e tabelas (≈2h15)

### 5.1 Apêndice (≈1h25)
- [ ] (5 min) Abrir `USPSC-TA-PosTextual/USPSC-Apendices.tex`, ver o exemplo do modelo e apagar o texto de exemplo.
- [ ] (12 min) Mover **Figuras 4 a 6** (decomposição e montagem do NFP) para `\chapter{Construção do No-Fit Polygon}\label{ap:nfp}`. No texto, trocar a figura por `(Apêndice~\ref{ap:nfp}, Figuras~\ref{fig:f4a} a~\ref{fig:f6b})`.
- [ ] (3 min) Compilar e conferir.
- [ ] (12 min) Mover **Figuras 7 a 10** (exemplo da BL) para `\chapter{Exemplo da heurística Bottom-Left}\label{ap:bl}` e ajustar as referências.
- [ ] (3 min) Compilar e conferir.
- [ ] (12 min) Mover **Figuras 14 a 18** (exemplo do BRKGA) para `\chapter{Exemplo do BRKGA}\label{ap:brkga}` e ajustar as referências.
- [ ] (3 min) Compilar e conferir.
- [ ] (12 min) Mover **Figuras 11, 12, 13 e 20** (layouts por instância) para `\chapter{Layouts obtidos}\label{ap:layouts}`. Deixar no texto só 1 exemplo (BL vs BRKGA) e referenciar o apêndice.
- [ ] (3 min) Compilar e conferir.
- [ ] (10 min) Mover a **Tabela 2** (e a 3, se decidiu mantê-la) para `\chapter{Tabelas completas}\label{ap:tab}` e ajustar `\ref{tab:t2}` no texto.
- [ ] (5 min) Compilar e conferir se o sumário e a lista de figuras estão certos.

### 5.2 Fonte e tabelas (≈1h)
- [ ] (20 min) Conferir se cada figura e tabela tem "Fonte: Elaborada pela autora." (formato no `notas.md`, copiado no passo 1.2).
- [ ] (10 min) Tabela 1 no padrão `\IBGEtab`: sem linhas verticais, com `\toprule`, `\midrule` e `\bottomrule`.
- [ ] (10 min) Tabela 4 no padrão `\IBGEtab`.
- [ ] (10 min) Tabela 2 (apêndice) no padrão `\IBGEtab`.
- [ ] (10 min) Tabela 3 (apêndice, se mantida) no padrão `\IBGEtab`.
- [ ] (opcional, 30 min) Criar uma tabela-resumo das 12 variantes da BL (variante, nº de melhores resultados, tempo médio) para o texto principal.

---

## BLOCO 6: fechar (≈2h15)

### 6.1 Considerações finais (≈45 min)
- [ ] (10 min) Reler o resumo da 1ª IC (`main.tex`) e escrever 2 ou 3 frases sobre ela.
- [ ] (15 min) Escrever as frases da 2ª IC com números: BL31 melhor em 12 de 29, BRKGA melhor, custo ~1500×.
- [ ] (10 min) Escrever 2 ou 3 itens de trabalhos futuros (rotação, repetir com sementes, mais instâncias, melhorar o código).
- [ ] (10 min) Acrescentar a limitação de uma execução por configuração.

### 6.2 Páginas (≈30 min)
- [ ] (5 min) Compilar do zero e anotar as páginas: ____
- [ ] (25 min) Se passar do limite, cortar nesta ordem: (a) mais figuras para o apêndice; (b) reduzir a escala dos layouts; (c) cortar a fundamentação do `main.tex`; (d) encurtar legendas e usar `\caption[curta]{longa}`.

### 6.3 Revisão final (≈1h)
- [ ] (10 min) Buscar `todo` e `textcolor{red` em todos os arquivos. Trocar a definição por `\newcommand{\todo}[1]{}`.
- [ ] (10 min) No PDF, Ctrl+F `??` para achar referência ou citação quebrada.
- [ ] (10 min) Conferir sumário, lista de figuras e lista de tabelas.
- [ ] (10 min) Conferir a lista de referências (autores, ano, "Acesso em:" nas `url`).
- [ ] (10 min) Conferir capa, folha de rosto, resumo e abstract.
- [ ] (5 min) Apagar arquivos gerados (`latexmk -C`), compilar do zero e confirmar que não há erro.
- [ ] (5 min) Copiar o PDF final com o nome definitivo.

---

## SE FALTAR TEMPO, CORTE NESTA ORDEM
1. Fundamentação do `main.tex` (4.4, último item)
2. Tabela-resumo das 12 variantes (5.2, opcional)
3. Frase do item 11 (apagar em vez de calcular)
4. Parágrafo D de limitações (reduzir a 2 frases)

## NUNCA CORTAR
Compilação, margens, introdução com referências, parágrafo da graduação, apêndice, Resumo/Abstract.
