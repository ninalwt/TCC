% ===== TABELA (padrão IBGE: sem linhas verticais) =====
\begin{table}[htb]
	\IBGEtab{%
		\caption{Título da tabela}%
		\label{tab:exemplo}
	}{%
		\begin{tabular}{ccc}
			\toprule
			Coluna 1 & Coluna 2 & Coluna 3 \\
			\midrule
			a & b & c \\
			d & e & f \\
			\bottomrule
		\end{tabular}%
	}{%
		\fonte{Elaborada pela autora.}%
	}
\end{table}
% \fonte já escreve "Fonte:" sozinho.
% Notas (opcional), dentro do último {}: \nota{Texto da nota.}
% Tabela larga: troque o tabular por \resizebox{\textwidth}{!}{\begin{tabular}...\end{tabular}}

% ===== FIGURA (legenda em cima, fonte embaixo) =====
\begin{figure}[htb]
	\caption{\label{fig:exemplo}Título da figura}
	\begin{center}
		% \includegraphics[width=0.8\textwidth]{imagens_bl/arquivo.png}
		% ou o \begin{tikzpicture} ... \end{tikzpicture}
	\end{center}
	\legend{Fonte: Elaborada pela autora.}
\end{figure}
% Aqui "Fonte:" você escreve à mão dentro do \legend.