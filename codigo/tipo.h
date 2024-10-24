enum Tipo{
	INT,
	CHAR,
	FLOAT,
	VOID,
	ARR, 
	STRING, 
	ERROR
};

const char* tipo_string(enum Tipo tipo){
	switch(tipo){
		case INT:
			return "int";
		case CHAR:
			return "char";
		case FLOAT:
			return "float";
		case VOID:
			return "void"; 
		case ARR:
			return "TIPOARREGLO";	
		case STRING:
			return "STRING"; 			
		case ERROR:
			return "TIPOERROR";				
	}
}

enum Tipo string_tipo(const char* str){
	if(strcmp(str, "int") == 0)
		return INT;
	else if(strcmp(str, "char") == 0)
		return CHAR;
	else if(strcmp(str, "float") == 0)
		return FLOAT;
	else if(strcmp(str, "void") == 0)
		return VOID; 
	else if(strcmp(str, "TIPOARREGLO") == 0)
		return ARR; 
	else if(strcmp(str, "STRING") == 0) 
		return STRING; 
	else
		return ERROR; 
}

enum Tipo deme_tipo(enum Tipo izq, enum Tipo der){
	if(izq == CHAR && der == CHAR)
		return CHAR; 

	if(izq == CHAR && der == INT)
	        return INT; 	

	if(izq == INT && der == CHAR)
		return INT;

	if(izq == CHAR && der == FLOAT)
		return FLOAT; 
	
	if(izq == FLOAT && der == CHAR)
		return FLOAT; 

	if(izq == INT && der == INT)
		return INT; 

	if(izq == INT && der == FLOAT)
		return FLOAT;

	if(izq == FLOAT && der == INT)
		return FLOAT; 

	if(izq == FLOAT && der == FLOAT)
	       	return FLOAT; 	

	return ERROR;
} 

bool es_menor(enum Tipo izq, enum Tipo der){
	return (izq == CHAR && der == INT)   ||
	       (izq == CHAR && der == FLOAT) ||
	       (izq == INT  && der == FLOAT);
}

bool es_operable(enum Tipo tipo){
	return tipo == CHAR || tipo == INT || tipo == FLOAT; 
}
