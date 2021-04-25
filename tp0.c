/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();
	log_info(logger,"Soy un log");
	//Loggear "soy un log"

	config = leer_config();
	valor=config_get_string_value(config,"CLAVE");
	log_info(logger,valor);
    puerto=config_get_string_value(config,"PUERTO");
	ip=config_get_string_value(config,"IP");
	//asignar valor de config a la variable valor

	//Loggear valor de config

	leer_consola(logger);
	

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//crear conexion
	conexion=crear_conexion(ip,puerto);

	//enviar CLAVE al servirdor

	enviar_mensaje(valor,conexion);
	paquete(conexion);

	terminar_programa(conexion, logger, config);
}

t_log* iniciar_logger(void)
{
	return log_create("tp0.log","TP0",is_active_console,LOG_LEVEL_INFO);
}

t_config* leer_config(void)
{
	return config_create("tp0.config");
}

void leer_consola(t_log* logger)
{
	char* leido;

	//El primero te lo dejo de yapa
	leido = readline(">");
	while(*leido!='\0'){
	log_info(logger,leido);
	free(leido);
	leido= readline(">");
	}
	free(leido);
}

void paquete(int conexion)
{
	//Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
	paquete=crear_paquete();
	leido=readline(">");
	while(*leido!='\0'){
    int largoCadena=strlen(leido)+1;
	agregar_a_paquete(paquete,leido,largoCadena);
	free(leido);
	leido=readline(">");
	}
	free(leido);
	enviar_paquete(paquete,conexion);
	eliminar_paquete(paquete);

}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}

