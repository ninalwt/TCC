# CRONOGRAMA TCC v2: do mais rápido ao mais longo, com 3 envios parciais

**Total ≈ 11h (+30 min opcionais).**
**Regra:** pausa de 10 min a cada 50 min. Travou 20 min? Anote e pule.

Arquivos que você já tem para colar: `correcoes_tcc.md` (A = números, B = localização dos erros, C = rascunhos C.1 a C.7), `tabelas_ibge.tex`, `refs_novas.bib`.

Legenda: **[P1]** obrigatório · **[P2]** importante · **[opc]** só se sobrar tempo

- [x] Diminuir margem (já feito)

---

## FASE 0: preparo (10 min)

- [ ] (2 min) **[P1]** Mandar para a orientadora: "As 20 páginas contam capa, resumo, listas e sumário? O apêndice conta? Posso tirar as 2 páginas em branco do modelo?"
- [ ] (3 min) **[P1]** Criar o `\todo` no preâmbulo: `\newcommand{\todo}[1]{\textcolor{red}{[PENDENTE: #1]}}`
- [ ] (5 min) Guardar `tabelas_ibge.tex`, `refs_novas.bib` e `correcoes_tcc.md` numa pasta fácil de achar (fora do projeto).

---

## FASE 1: compilar (≈1h10) **[P1]**
Sem isso não dá para mandar nada. Se algum passo já foi feito, marque.

- [ ] (3 min) `USPSC-TCC-NINA.tex`: `\bibliography{USPSC-bib/bib.bib}` vira `\bibliography{USPSC-bib/bib}`
- [ ] (5 min) `bib.bib`, entrada `arenales`: autores na ordem Arenales, Armentano, Morabito, Yanasse; "Marcos"; apagar o comentário `% <- ADICIONE...`
- [ ] (8 min) Renomear a chave `key` para `mundim2017` e trocar `\cite{key}` por `\cite{mundim2017}` (Ctrl+Shift+H). Conferir o 3º autor (de Queiroz, Thiago Alves).
- [ ] (15 min) Apagar o texto do modelo nos capítulos: Cap1 (frase "Parte inicial..."), Cap3 ("Apresentar as conclusões..."), Cap2 (da linha 9 até antes de `\section{Formulação...}`; manter o `\chapter{Desenvolvimento}`).
- [ ] (15 min) Arquivo principal: apagar os `\include` de Errata, Dedicatoria, Epigrafe, AbreviaturasSiglas, Simbolos (e Agradecimentos, se não for escrever); o bloco `\listofquadro*`; `chemfig`, `chemmacros`, `lipsum`. Os 2 `\includepdf{...PaginaEmBranco.pdf}` só depois da resposta da orientadora.
- [ ] (20 min) Compilar (2 vezes). Resolver só o primeiro `!` de cada vez. Anotar páginas: ____
- Obs.: **não precisa** mexer nos `adjustwidth` das tabelas antigas, porque você vai substituí-las inteiras na Fase 2.

---

## FASE 2: seções rápidas (≈2h40) → **ENVIO 1**
Tudo aqui é colar e conferir. Os rascunhos já têm os seus números.

- [ ] (15 min) **[P1] Resumo:** colar C.5 em `USPSC-TA-PreTextual/USPSC-Resumo.tex`. Conferir que tem entre 150 e 250 palavras e as palavras-chave.
- [ ] (15 min) **[P1] Abstract:** colar C.6 em `USPSC-Abstract.tex`. Preencher o título em inglês (`\titleabstract` e `\tituloadic` em `USPSC-TCC-pre-textual-ICMC.tex`).
- [ ] (15 min) **[P1] Considerações Finais:** colar C.7 em `USPSC-Cap3-Conclusao.tex`. Apagar o texto antigo. Compilar.
- [ ] (5 min) **[P1]** Cap2, frase das razões: colar C.1 (dighe1 0,710 e poly5A 0,895).
- [ ] (5 min) **[P1]** Cap2, frase das quatro melhores: colar C.2.
- [ ] (10 min) **[P1]** Cap2, parágrafo "É possível perceber...": colar C.3 (BRKGA vs BL, 4,4%, 1500×, 900 chamadas).
- [ ] (10 min) **[P1]** Cap2, fim da comparação: colar C.4 (limitações).
- [ ] (30 min) **[P1] Ortografia e escrita:** aplicar a lista B (Cap2, Cap3), usando Ctrl+F com o trecho entre aspas, porque as linhas mudaram.
- [ ] (30 min) **[P1] Tabelas:** para cada uma das 4 tabelas do Cap2, apagar do `\begin{adjustwidth}` até o `\end{adjustwidth}` e colar o bloco correspondente de `tabelas_ibge.tex` (mesmo `\label`). Compilar. Depois decidir: Tabela 3 fica ou vai para o apêndice? ________
- [ ] (10 min) **[P2]** Conferir no `.txt` do programa os 5 valores que divergem (poly1A, poly2A, poly3b, poly4b, poly5b) e corrigir nas tabelas.
- [ ] (5 min) **[P1]** Colocar `\todo{Introdução será reescrita com mais referências}` no topo do Cap1 e `\todo{Apêndice com as figuras}` onde for ficar, para a orientadora ver o que falta.

### ENVIO 1 (10 min)
- [ ] Compilar do zero, abrir o PDF, ver se não há `??` em Resumo, Abstract, Cap2 (resultados) e Cap3.
- [ ] Mandar o PDF para a orientadora: "Segue a versão parcial: Resumo, Abstract, resultados revisados e Considerações Finais. Ainda faltam: Introdução, parágrafo da graduação, apêndice e referências."
- [ ] Anotar aqui a data/hora do envio: ________

---

## FASE 3: seções médias (≈2h40) → **ENVIO 2**

### 3.1 Apêndice [P1] (≈1h45)
- [ ] (5 min) Abrir `USPSC-TA-PosTextual/USPSC-Apendices.tex`, ver o exemplo do modelo e apagar o texto de exemplo.
- [ ] (12 min) Mover as **Figuras 4 a 6** (NFP) para `\chapter{Construção do No-Fit Polygon}\label{ap:nfp}`. No texto: `(Apêndice~\ref{ap:nfp}, Figuras~\ref{fig:f4a} a~\ref{fig:f6b})`. Compilar (3 min).
- [ ] (12 min) Mover as **Figuras 7 a 10** (exemplo da BL) para `\chapter{Exemplo da heurística Bottom-Left}\label{ap:bl}` e ajustar as referências. Compilar (3 min).
- [ ] (12 min) Mover as **Figuras 14 a 18** (exemplo do BRKGA) para `\chapter{Exemplo do BRKGA}\label{ap:brkga}` e ajustar. Compilar (3 min).
- [ ] (12 min) Mover as **Figuras 11, 12, 13 e 20** (layouts) para `\chapter{Layouts obtidos}\label{ap:layouts}`. Deixar no texto só 1 exemplo. Compilar (3 min).
- [ ] (10 min) Mover a **Tabela 2** (e a 3, se decidiu) para `\chapter{Tabelas completas}\label{ap:tab}` e ajustar `\ref{tab:t2}`.
- [ ] (20 min) Em cada figura, passar o `\caption` para antes do conteúdo e acrescentar `\legend{Fonte: Elaborada pela autora.}` no fim (formato no `notas.md`).

### 3.2 Coerência restante [P2] (≈45 min)
- [ ] (10 min) Algoritmo da BL, passo 2.d: acrescentar que cada interseção calculada precisa ser **validada** (fora de todos os NFPs e dentro do IFP).
- [ ] (15 min) Notação: `M` e `C` colidem. Trocar na seção do BRKGA por `p_m`, `p_c` (e `p`, `p_e`, `G`, `\rho`), conforme a seção A de `correcoes_tcc.md`.
- [ ] (10 min) Definir otimização e meta-heurística em 1 frase cada (se a nova Introdução ainda não os define).
- [ ] (5 min) Tabela 1: acrescentar o critério de desempate (BL22, BL41 e BL42 empatam com 2 melhores resultados).
- [ ] (5 min) **[P1]** Compilar e contar as páginas: ____ . Se passar de 20, já decida os cortes agora.

### ENVIO 2 (10 min)
- [ ] Compilar do zero, ver o PDF.
- [ ] Mandar: "Segue a versão com o apêndice e o Capítulo 2 revisado. Ainda faltam a Introdução e o parágrafo da graduação."

---

## FASE 4: seções longas (≈3h10, +30 min opcionais) → **ENVIO 3**
A Introdução e o parágrafo da graduação foram **pedidos pela orientadora**: não corte.

### 4.1 Referências [P1] (≈35 min)
- [ ] (5 min) Colar `refs_novas.bib` no fim de `USPSC-bib/bib.bib`.
- [ ] (25 min) Conferir no Google Acadêmico as 6 entradas **não verificadas**: `baker1980` (páginas), `albano1980` (páginas), `bean1994`, `art1966`, `garey1979`, `esicup` (data de acesso). Corrigir o que divergir.
- [ ] (5 min) Compilar e ver se o `.bbl` gerou sem erro.

### 4.2 Introdução [P1] (≈1h30)
Rascunho A está na minha resposta de revisão (seção 7). **Use `dowsland2002`, não `dowsland1998`; `bennell2009` = `irregular`, `bennell2008` = `geometry`.**
- [ ] (5 min) Abrir `USPSC-Cap1-Introducao.tex` e o rascunho A lado a lado.
- [ ] (15 min) Colar o parágrafo 1 (aplicações e tipologia): `irregular`, `geometry`, `dyckhoff1990`, `wascher2007`.
- [ ] (15 min) Colar o parágrafo 2 (NP-difícil, BL, BRKGA, NFP): `garey1979`, `baker1980`, `albano1980`, `dowsland2002`, `burke2006`, `bean1994`, `goncalves2011`, `goncalves2013`, `art1966`.
- [ ] (10 min) Colar o parágrafo 3 (objetivo): `esicup`.
- [ ] (10 min, opc) Acrescentar uma frase com `\cite{mundim2017}` e `\cite{containers}`.
- [ ] (10 min) Apagar os parágrafos antigos redundantes e o `\todo`/`\textcolor{red}` da Introdução.
- [ ] (10 min) Atualizar o parágrafo de organização do texto ("Seção~\ref{...}") conferindo os `\label`.
- [ ] (5 min) Compilar e procurar `?` nas citações.

### 4.3 Parágrafo da graduação [P1] (≈35 min)
- [ ] (10 min) No papel: 3 disciplinas que ajudaram e por quê (1 linha cada).
- [ ] (10 min) No papel: 1 ou 2 coisas que faltaram ou foram aprendidas por conta própria.
- [ ] (10 min) Colar o rascunho B no fim da Introdução e preencher os colchetes.
- [ ] (5 min) Ler em voz alta e cortar o que estiver forçado.

### 4.4 Fundamentação do `main.tex` [opc] (30 min)
- [ ] (10 min) Colar o rascunho C antes da seção do IFP/NFP.
- [ ] (10 min) Adaptar a notação.
- [ ] (10 min) Acrescentar a fórmula do IFP com α_D, β_D, γ_D.

### 4.5 Páginas [P1] (30 min)
- [ ] (5 min) Compilar do zero e anotar as páginas: ____
- [ ] (25 min) Se passar do limite, cortar nesta ordem: (a) fundamentação (4.4); (b) mais figuras para o apêndice; (c) reduzir a escala dos layouts; (d) `\caption[curta]{longa}`.

### ENVIO 3 (10 min)
- [ ] Compilar do zero, ver o PDF.
- [ ] Mandar a versão completa para revisão final, perguntando sobre as páginas em branco e o limite de 20 páginas, se ainda não respondeu.

---

## FASE 5: fechar (≈1h05) **[P1]**
Faça depois das correções da orientadora.

- [ ] (10 min) Buscar `todo` e `textcolor{red` em todos os arquivos. Trocar a definição por `\newcommand{\todo}[1]{}`.
- [ ] (10 min) No PDF, Ctrl+F `??` para achar referência ou citação quebrada.
- [ ] (10 min) Conferir sumário, lista de figuras e lista de tabelas.
- [ ] (10 min) Conferir as referências (autores, ano, "Acesso em:" nas `url`).
- [ ] (10 min) Conferir capa, folha de rosto, resumo e abstract.
- [ ] (5 min) Ficha catalográfica e folha de aprovação: perguntar à biblioteca/coordenação como obter os oficiais.
- [ ] (5 min) Apagar arquivos gerados (`latexmk -C`), compilar do zero e confirmar que não há erro.
- [ ] (5 min) Copiar o PDF final com o nome definitivo.

---

## SE FALTAR TEMPO, CORTE NESTA ORDEM
1. Fundamentação do `main.tex` (4.4)
2. Frase do `mundim2017`/`containers` na Introdução (4.2, opc)
3. Coerência restante, itens de notação e definições (3.2)
4. Parágrafo de limitações C.4 (reduzir a 2 frases)

## NUNCA CORTAR
Compilação, Resumo/Abstract, Introdução com referências, parágrafo da graduação, apêndice, margens.