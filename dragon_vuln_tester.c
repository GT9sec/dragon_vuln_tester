/*
 * Dragon Vulnerability Tester 🐉
 * 
 * Autor: GT9sec e UprisingHK
 * 
 * Descrição: Esta ferramenta permite testar vulnerabilidades em sites WordPress
 * buscando usuários e postagens através da API do WordPress.
 * 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <curl/curl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <jansson.h>

void limpa(){
    system("clear");
}

void imprime_banner() {
    const char *banner[] = {
        "___________________¶¶",
        "____________________¶¶__¶_5¶¶",
        "____________5¶5__¶5__¶¶_5¶__¶¶¶5",
        "__________5¶¶¶__¶¶5¶¶¶¶¶5¶¶__5¶¶¶5",
        "_________¶¶¶¶__¶5¶¶¶¶¶¶¶¶¶¶¶__5¶¶¶¶5",
        "_______5¶¶¶¶__¶¶¶¶¶¶¶¶¶¶¶_5¶¶__5¶¶¶¶¶5",
        "______¶¶¶¶¶5_¶¶¶¶¶¶¶¶¶¶¶¶¶5¶¶¶__¶¶¶¶5¶5",
        "_____¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_¶¶¶¶¶¶¶5",
        "____¶¶¶¶¶¶¶_¶¶¶5¶¶¶¶5_¶¶¶¶¶5_5¶_¶¶¶¶¶¶¶¶5",
        "___¶¶¶¶¶¶¶¶__5¶¶¶¶¶¶5___5¶¶¶¶__5¶¶¶¶¶¶¶¶¶5",
        "__¶¶¶¶¶¶¶¶¶¶5__5¶¶¶¶¶¶5__5¶¶5_5¶¶¶¶¶¶¶¶¶¶¶",
        "_5¶¶¶¶¶¶¶¶¶¶¶¶_5¶¶¶¶¶¶¶¶¶5__5¶¶¶¶¶¶¶¶¶¶¶¶¶5",
        "_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_5¶¶¶¶",
        "5¶¶¶¶¶¶¶¶¶¶¶¶5___5¶¶¶¶¶¶¶5__¶¶¶¶5_¶¶¶5_¶¶¶¶",
        "¶¶¶¶¶¶¶¶_¶¶5_5¶5__¶¶¶¶¶¶¶¶¶5_5¶¶¶_5¶¶¶_5¶¶¶5",
        "¶5¶¶¶¶¶5_¶¶_5¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶5_5¶¶_5¶¶¶_¶¶¶5",
        "¶¶¶¶_¶¶__¶__¶¶¶¶¶¶5_5¶¶¶¶¶¶¶¶¶¶5_¶¶_5¶¶_5¶¶¶",
        "¶¶¶5_5¶______5¶¶5¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶5_¶¶_5¶5_¶5¶",
        "5¶¶____5¶¶¶¶5_____5¶¶¶¶¶¶¶5_¶¶¶¶¶5_¶__¶¶_5¶¶",
        "_¶¶__5¶¶¶¶¶¶¶¶¶¶5____5¶¶¶¶¶¶_¶¶¶¶¶_____¶5_¶¶",
        "_¶¶___5¶¶¶¶¶¶¶¶¶__________5¶5_¶¶¶¶¶____¶¶_¶¶",
        "_¶¶_______5¶¶¶¶¶¶5____________¶¶¶¶¶_____¶_¶¶",
        "_5¶5________5¶¶_¶¶¶¶5________5¶¶¶¶¶_______¶¶",
        "__¶¶__________¶___¶¶¶¶¶5___5¶¶¶¶¶¶5_______¶5",
        "__¶¶____________5¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶________¶",
        "___¶________________5¶¶¶¶¶¶¶¶5_¶¶",
        "___¶__________5¶¶¶¶¶¶¶¶5¶¶¶5__5¶5",
        "_____________________5¶¶¶5____¶5"
   
       
};

 for (int i = 0; i < sizeof(banner) / sizeof(banner[0]); i++) {
        printf("%s\n", banner[i]);
    }
}


size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp){
    size_t realsize = size * nmemb;		
    if(realsize + strlen(userp) < 4096){
       strncat(userp, contents, realsize);
    }
    return realsize;
}

void salvar_em_arquivos(const char *dados){
    FILE *arquivo = fopen("resultados.txt", "a");
    if(arquivo != NULL){
        fprintf(arquivo, "%s\n", dados);
	fclose(arquivo);
	printf("\033[0;32;1mResultados salvos em 'resultados.txt'.\003[0m\n");
    }else{
        printf("\033[0;32;1mErro ao salvar os resultados...\033[0m\n");
    }
}

void exibir_resultados_formatados(const char *dados, const char *endpoint){
    printf("\033[0;32;1mUsuários encontrados no endpoint: %s\n", endpoint);
    printf("---------------------------------------------------\n");
    printf("%s\n", dados);
    printf("------------------------------------------------\n\n");
    salvar_em_arquivos(dados);

}

void tentar_buscar_usuarios(const char *url){
    CURL *curl;
    CURLcode res;
    char response[4096] = {0};

    const char *endpoints[] = {
        "/wp-json/wp/v2/users/?per_page=100&page=1",
	"/wp-json/wp/v2/users?context=edit",
	"/wp-json/?rest_route=/wp/v2/users&per_page=100&page=1",
	"/wp-json/?rest_route=/wp/v2/users&context=edit",
	"/wp-json/wp/v2/search?search=admin",
	"/wp-json/wp/v2/comments",
	"/wp-json/wp/v2/media",
        "/wp-json/wp/v2/categories",
        "/wp-json/wp/v2/tags",
        "/wp-json/wp/v2/pages",
        "/wp-json/wp/v2/posts",
	"/wp-json/wp/v2/settings",
	"/wp-json/wp/v2/comments?per_page=100",
	"/wp-json/wp/v2/users/me"
    
    };

    int total_endpoints = sizeof(endpoints) / sizeof(endpoints[0]);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl){
        for(int i = 0; i < total_endpoints; i++){
	
	char full_url[512];
	snprintf(full_url, sizeof(full_url), "%s%s", url, endpoints[i]);


	curl_easy_setopt(curl, CURLOPT_URL, full_url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	memset(response, 0, sizeof(response));
	printf("Testando: %s\n", full_url);

	res = curl_easy_perform(curl);

	if(res == CURLE_OK && strlen(response) > 0){
	    exibir_resultados_formatados(response, endpoints[i]);
	}else{
	    printf("\033[0;31;1mFalha ao buscar usuários no endpoint: %s\n", endpoints[i]);
	}
	
	}

	curl_easy_cleanup(curl);

    }else{
        printf("Erro ao inicializar cURL.\n");	    
    
    }
    curl_global_cleanup();


}

int main(){
    limpa();
    imprime_banner();

    char url[256];
    printf("Digite a URL do alvo: ");
    scanf("%s", url);

    tentar_buscar_usuarios(url);
    return 0;


}
    
