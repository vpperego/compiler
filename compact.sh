#!/bin/bash
tar --exclude='*~' --exclude='testes' --exclude='testes/*' --exclude='.git*' --exclude='*.txt' --exclude='*.tgz' --exclude='.DS_Store' --exclude='*.pdf' --exclude='*.sh' --exclude='*.out' --exclude='*.o' -cvzf etapa4.tgz .
