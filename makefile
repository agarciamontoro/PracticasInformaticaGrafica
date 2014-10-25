########################################################################
##
## Prácticas IG, curso 2014-15
## Carlos Ureña, Oct-2014
## 
## archivo 'make' para compilar, enlazar y ejecutar
## invocar von 'make'
## genera archivo ejecutable 'prac', usando todos los .cpp/.cc/.c presentes
##
########################################################################

.SUFFIXES:
.PHONY: start, exec, all, compile, clean, tar

INC					:= ./inc
BIN					:= ./bin
OBJ					:= ./obj
SRC					:= ./src


target_name         := $(BIN)/prac
opt_dbg_flag        := -g
exit_first          := -Wfatal-errors
warn_all            := -Wall
##warn_all          :=
units_ext           := $(wildcard $(SRC)/*.cpp $(SRC)/*.cc $(SRC)/*.c)
headers             := $(wildcard $(INC)/*.hpp $(INC)/*.hh $(INC)/*.h)
##units_ext           :=  main practica1 error-ogl

gl_libs_base        := -lglut -lGLU 
gl_lib_file         := -lGL

gl_lib_file_nv      := /usr/lib/nvidia-331/libGL.so
ifeq ($(wildcard $(gl_lib_file_nv)),$(gl_lib_file_nv))
   gl_lib_file      := $(gl_lib_file_nv)
endif

gl_libs             := $(gl_libs_base) $(gl_lib_file)
other_ld_libs       := 
gtk_c_flags         := 
gtk_ld_libs         := 


units               := $(basename $(units_ext))
objs                := $(addprefix $(OBJ)/, $(addsuffix .o, $(notdir $(units))))
c_flags             := -I $(INC) $(src_dir) $(opt_dbg_flag) $(exit_first) $(warn_all) $(gtk_c_flags)
ld_libs             := $(gtk_ld_libs) $(gl_libs) $(other_ld_libs)

start:
	@make --no-print-directory exec

exec: $(target_name)
	@echo "ejecutando " $(target_name) " ...."
	./$(target_name)

all:
	echo $(objs)
	make clean
	make compile

compile: $(target_name)
	@echo "compilando fuentes: " $(units_ext)
	@make --no-print-directory $(target_name)

$(target_name) : $(objs)
	@echo `tput bold`---------------------------------------------------------------
	@echo "Enlazando      :" $(target_name) 
	@echo "Unidades(ext)  :" $(units_ext) 
	@echo "Objetos        :" $(objs) 
	@tput sgr0
	g++ -o $(target_name) $(objs) $(ld_libs) 
	@echo ---------------------------------------------------------------
	
	
$(OBJ)/%.o: $(SRC)/%.cpp $(headers)
	@echo `tput bold`---------------------------------------------------------------
	@echo Compilando: $(notdir $<) 
	@tput sgr0
	@g++ $(c_flags) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.cc $(headers)
	@echo `tput bold`---------------------------------------------------------------
	@echo Compilando: $(notdir $<) 
	@tput sgr0
	@g++ $(c_flags) -c $< -o $@
	
$(OBJ)/%.o: $(SRC)/%.c $(headers)
	@echo `tput bold`---------------------------------------------------------------
	@echo Compilando: $(notdir $<) 
	@tput sgr0
	@g++ $(c_flags) -c $< -o $@

clean:
	rm -f $(OBJ)/*.o $(target_name)
	
tar:
	tar czvf archivos_prac_1.tgz *.c* *.h* *.ply makefile




