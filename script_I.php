	<?php
	//
	//  Script I de pré processamento da BDO
	//  S_MEMISP+AR
	//
	//  Created by Rafael Stoffalette João on 11/1/14.
	//  Copyright (c) 2015 Rafael Stoffalette João. All rights reserved.
	//

if(isset($primeira_etapa_processamento)){
	require_once($_SERVER['DOCUMENT_ROOT'] . "../includes/excel_reader2.php"); // plugin para leitura de arquivos xls via php
	$coluna = 3;													// disponível em http://code.google.com/p/php-excel-reader/
	$fp = fopen("bdo.txt", "w");  // arquivo de saída
	for($numarqs = 1; $numarqs < 1500; $numarqs++){ // cada registro de compra tem como nome os numeros de 1 a 1500
		$cesta =  Array();                            // referente a cada identificador da compra
		$data = new Spreadsheet_Excel_Reader($numarqs.'.xls'); //abre cada um dos registros de compra
		$totalLinhas = $data->rowcount();            // calcula quantos itens tem na compra (n. de  linhas)
		for ($i = 8; $i <= $totalLinhas; $i++) {     // coloca cara item no array $cesta
	        	if($data->val($i,3) != "") 
	        		array_push($cesta,$data->val($i,3));
	  }

	  sort($cesta);                 // ordena os itens da compra
	  $dado = $data->val(5,1);      // elemento [5][1], data da compra
	  $dado = strtolower(str_replace(' ', '', $dado)); // remove espaços em branco da data
	  $dado = str_replace(".", "", $dado);  // remove pontos da data
	  fwrite($fp,"\n(");                 // insere uma quebra de linha (cada compra em uma linha)
	  fwrite($fp,$dado);                   // grava a data como um item no arquivo
	  fwrite($fp,",");                    //  insere o separador de itens ","
	  $dado = $data->val(5,2);             // elemento [5][1], hora da compra
	  $dado = strtolower(str_replace(' ', '', $dado)); // remove espaços em branco da hora
	  $dado = str_replace(".", "", $dado);  // remove pontos da hora
	  fwrite($fp,$dado);    // grava a hora como um item no arquivo
	  fwrite($fp,")(");     // finaliza o itemset da data,hora e inicia o de itens da compra

	  foreach ($cesta as $key => $value) { // para cada item da compra
	  	$string = strtolower(str_replace(' ', '', $value));  // remove os espaços em branco da descrição do item
	  	$palavra = ereg_replace("[^a-zA-Z0-9_]", "",$string); // remove os caracteres especiais da descrição do item
	  	$string = str_replace(".", "", $palavra);  // remove os pontos da descrição do item
	  	fwrite($fp, trim($string));      // grava o item da compra  no arquivo
	    if(!end($cesta)) fwrite($fp, ","); // se não for o último elemento do array insere uma virgula para separar os itens
	  }
	  fwrite($fp, ")"); //finaliza o itemset com ")"
	}
	fclose($fp); // fecha o arquivo
}else{

	 $lines = file ('bdo.txt'); // arquivo de entrada (BDO em seu estado bruto) 

	if(isset($_POST['novaDB'])){ // procedimento para gerar o arquivo de saída, com a BDO processada, chamado
		$fp = fopen("bdo-processado.txt", "w"); // arquivo de saída
		foreach ($lines as $line_num => $line) { // percorrendo as linhas (compras) da BDO, uma a uma
			$array  = explode(',', $line);       // converte cada registro de compra em um array de itens
		  	sort($array);						 // ordena lexicograficamente os itens dentro do array 
		  	$result = array_unique($array);		 // elimina as redundâncias 
		  	$novalinha = implode(',', $result);  // transforma o array ordenado e com itens sem repetição em uma nova linha
		  	fwrite($fp, $novalinha);			 // grava a linha no arquivo de saída (BDO processada)
		}
		fclose($fp);
	}
	elseif(isset($_POST['trocaNome'])){		// procedimento para substituir nomes de itens chamado
		$selected = $_POST['trocaNome'];	// Conjunto de nomes selecionados para 
		$novoNome = $_POST['novoNome'];		// novo nome que irá representar os itens selecionados
	 	$path_to_file = 'bdo.txt';			// arquivo de entrada (BDO em seu estado bruto)
	 	$file_contents = file_get_contents($path_to_file); // a BDO inteira é copiada para uma variavel

		foreach ($selected as $key => $value) {		// para cada item selecionado a ter o nome trocado
			$search_string  = $value;				
			$replace_string = $novoNome;
			$file_contents = str_replace($search_string,$replace_string,$file_contents);
		}											// é feito a busca e substituição dos nomes
		file_put_contents($path_to_file,$file_contents);
	}						// a variável que contém os itens com novos nomes é inserida no arquivo de volta
	 

	 echo "\n---------------------------------BDO------------------------------\n";
	$cesta = array();				
	foreach ($lines as $line_num => $line) { // percorrendo as linhas (compras) da BDO, uma a uma
	  $array  = explode(',', $line);		 // converte cada registro de compra em um array de itens
	  						 

	  foreach ($array as $key => $value) {	// para cada item dentro de cada compra da BDO
	    array_push($cesta,htmlspecialchars($value)); // armazena cada item no array $cesta
	  }
	}
	sort($cesta);							// ordena lexicograficamente os itens dentro do array 
	$cont=0;
	foreach ($cesta as $chave => $valor) { // percorre a lista com todos os itens contidos na BDO
		$cont++;
		$valor  = str_replace("(", "",$valor); // ignora "(" 
		$valor  = str_replace(")", "",$valor); // ignora ")"
		$valor  = str_replace(",", "",$valor); // ignora ","
	  	echo"<br /><input type='checkbox' name='trocaNome[]' value='".$valor."' />";
	  	echo " 	".$cont." - ".$valor;	 // imprime cada item de forma ordenado e com uma caixa de seleção
	}									// a fim de possibilitar selecionar o item e trocar seu nome.
}
	?>	