#ifndef TRABALHO1_SB_MONTADOR_ERROR_H_
#define TRABALHO1_SB_MONTADOR_ERROR_H_

void lexicalError(const std::string& line, int lineCounter);
void syntaticalError(const std::string& line, int lineCounter);
void semanticalError(const std::string& line, int lineCounter);

#endif //TRABALHO1_SB_MONTADOR_ERROR_H_
