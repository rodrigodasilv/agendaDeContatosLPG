# Agenda de contatos LPG

### O objetivo deste trabalho consiste em desenvolver um programa para manter as informações de uma agenda de contatos utilizando variáveis compostas. A estrutura do contato deve conter um código de identificação, nome, e-mail e celular. 

O programa deve conter um menu inicial com 5 opções: 

i) incluir um novo contato; - *Willian* <br/>
ii) excluir um contato existente; - *Rodrigo* <br/>
iii) alterar um contato existente; <br/>
iv) listar todos os contatos cadastrados; <br/>
v) localizar um contato. <br/>

Na operação de inclusão de um novo contato, **considerar um identificador exclusivo para cada contato, se for o  caso opte por incrementar uma unidade no último identificador válido de um contato.** 

O e-mail precisa ser um valor válido, isto é, **deve ser validada a existência de um arroba @.** 

A opção para localizar um contato deve ser implementada por meio de uma **busca aproximada pelo nome do contato, considerando uma distância de edição de até 5 operações e ordenando o resultado da busca de forma crescente** para exibir os melhores resultados por primeiro. 

Os dados da agenda de contatos **devem ser salvos em arquivo,** garantindo que os dados serão armazenados de forma durável.
