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
#include <string.h> //O terror do GT9Fraga SKSKSK, brincadeira, te amo s2
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
    strcat(userp, contents);
    return size * nmemb;

}

char *buscar_usuarios(){
    char url[256];
    printf("Digite a URL do alvo: ");
    scanf("%s", url);

    strcat(url, "/wp-json/wp/v2/users/?per_page=100&page=1");

    CURL *curl;
    CURLcode res;
    static char response[4096] = {0};

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	res = curl_easy_perform(curl);

	if(res != CURLE_OK){
	    printf("Erro ao buscar usuários: %s\n", curl_easy_strerror(res));
	    return NULL;
	}


        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return response;


}

int main(){
    limpa();
    imprime_banner();

    char *usuarios_json = buscar_usuarios();
    if(usuarios_json && strlen(usuarios_json) > 0){
        printf("\033[0;34;1mUsuários achados hehe: \n");
	printf("%s\n", usuarios_json);
    
    }else{
        printf("\033[0;31;1mNenhum usuários encontrado :(\n");
    }

    return 0;


}
    

