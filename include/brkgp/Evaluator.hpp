// SPDX-License-Identifier: MIT
// Copyright (C) 2023

#pragma once

// C
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// C++
#include <stack>
#include <vector>
//
#include <brkgp/Evaluator.hpp>
#include <brkgp/PrintIO.hpp>
#include <kahan-float/kahan.hpp>

double execBinaryOp(int idop, double v1, double v2,
                    const std::vector<char>& operationsBi) {
  if (operationsBi[idop] == '+') {
    if (abs(v1) == INFINITY) return INFINITY;
    return v1 + v2;
  }
  if (operationsBi[idop] == '-') {
    if (abs(v1) == INFINITY) return INFINITY;
    return v1 - v2;
  }
  if (operationsBi[idop] == '*') {
    if ((abs(v1) == INFINITY && v2 == 0) || (v1 == 0 && abs(v2) == INFINITY))
      return INFINITY;
    return v1 * v2;
  }
  if (operationsBi[idop] == '/') {
    if (v2 < 0.000001) return INFINITY;
    if (abs(v2) == INFINITY) return 0;
    return v1 / v2;
  }
  return 0.0;
}

double execUnaryOp(int idop, double v1, const std::vector<char>& operationsU) {
  if (operationsU[idop] == 's') {
    if (v1 == INFINITY) return INFINITY;
    return sin(v1);
  }

  if (operationsU[idop] == 'c') {
    if (v1 == INFINITY) return INFINITY;
    return cos(v1);
  }
  if (operationsU[idop] == 'i') return v1;
  if (operationsU[idop] == 'a') return v1 * v1;
  if (operationsU[idop] == 'v') return v1 * v1 * v1;
  if (operationsU[idop] == 'r') {
    if (v1 < 0)
      return INFINITY;
    else
      return ::pow(v1, 1.0 / 2.0);
  }
  return 0.0;
}

// error between values v1 and v2 RMSE
double computeError(double v1, double v2) {
  // square
  return sqrt((v1 - v2) * (v1 - v2));
}

// stackAdjustment: ajusta chaves aleatórias do indivíduo, caso seja
// impossível decodificá-lo! Por exemplo, operações binárias seguidas
// sem operandos disponíveis na pilha!
// IDEIA: usar realStackValue para representar o fim do indivíduo, ao
// invés de ajustá-lo!
// EXEMPLO: fazer vetor simples para x² (só precisa de stackLen=2)!
// IDEIA 2: QUANDO PARAR DECODIFICAÇÃO?
//  - Hipótese: quando stack size = 1?
//  - TALVEZ... Marcador de chave aleatória que só é ativado se stack size = 1.
// IDEIA 3: INVOCAR 'mathomatic' para simplificar equações... Fazer só no Best?
// IDEIA 4: USAR UNIDADE SIMBOLICA COMO CRITERIO DE SIMPLICIDADE AO LONGO DA
// EXECUCAO...
//
int stackAdjustment(Vec<chromosome>& individual, int stackLen, int nVars,
                    int nConst, int maxConst, int seed) {
  // 5303   358   3064   9156   4199   1320   636   7306   2445   6166   3572
  // 8249   4290   4389   4790   567   9692   202   3913   498 1      -1      0
  // 2     0      -1     -1     1     -1     1       0     2       0     0 0 -1
  // 2      -1     0     -1 1       1       0     2     0       -1     1     1
  // -1     1       0     2       0     0      0     -1     2      -1     0 1
  int somador = 0;
  int auxSomador = 0;
  int decodValue = 0;
  int contConst = 0;
  int idConst = 0;
  int trueStackLen = 0;
  for (int i = 0; i < stackLen; i++) {
    // TODO(igormcoelho): verificar esse número 4!!!
    int my_floor1 = ::floor((individual[i] / 10000.0) * 4);  // [0,3]
    assert(my_floor1 <= 3 && my_floor1 >= 0);                // NOLINT
    decodValue = my_floor1 - 1;                              // [-1,2]
    //
    int my_floor2 =
        ::floor((individual[stackLen + i] / 10000.0) * (nVars + nConst));
    idConst = my_floor2 - nConst;
    // TODO(igormcoelho): verificar esse número 2!!!
    // [-1,0,1] ?
    if (decodValue != 2) {
      auxSomador += decodValue;
    }
    // se == 2, faz nada???
    // ???
    if (auxSomador < 1) {
      // ALTERANDO OPERAÇÕES!
      if (individual[i] < 2500) {
        // std::cout << "WARNING! ALTERANDO individual COD0!" << std::endl;
        individual[i] += 5000;
      } else if (individual[i] >= 7500) {  // se der testar depois, no caso i=0
        // std::cout << "WARNING! ALTERANDO individual COD1!" << std::endl;
        individual[i] -= 2500;
      } else {  // se der testar depois, no caso i=0
        // std::cout << "WARNING! ALTERANDO individual COD2!" << std::endl;
        individual[i] += 2500;
      }
      auxSomador = somador + 1;
    }
    if (auxSomador > (stackLen - i)) {
      if (somador == 1) {
        // std::cout << "WARNING! ALTERANDO individual COD3!" << std::endl;
        individual[i] += 2500;
        auxSomador = 1;
      } else if (somador > 1) {
        if ((individual[i] >= 2500) && (individual[i] < 5000)) {
          // std::cout << "WARNING! ALTERANDO individual COD4!" << std::endl;
          individual[i] -= 2500;
        } else if (individual[i] >=
                   7500) {  // se der testar depois, no caso i=0
          // std::cout << "WARNING! ALTERANDO individual COD5!" << std::endl;
          individual[i] -= 7500;
        } else {  // se der testar depois, no caso i=0
          // std::cout << "WARNING! ALTERANDO individual COD6!" << std::endl;
          individual[i] -= 5000;
        }
        auxSomador = somador - 1;
      }
    }
    if ((decodValue == 1) && idConst < 0) {
      contConst++;
      if (contConst > maxConst) {
        srand(seed);
        // std::cout << "WARNING! ALTERANDO individual COD7!" << std::endl;
        individual[stackLen + i] =
            ((10000.0 / (nVars + nConst)) * nConst) +
            ((10000.0 / (nVars + nConst)) * (rand() % nVars) + 1);  // NOLINT
        seed++;
      }
    }
    somador = auxSomador;
    if (individual[i] < 7500) trueStackLen++;
  }
  return trueStackLen;
}

double solutionEvaluator(const RProblem& problem,
                         const Vec<chromosome>& individual,
                         const Scenario& other, int training, int idSol) {
  // idSol: Identifier of Solution in Population (Good for DEBUG!)
  // problem counters
  const int nVars = problem.nVars;
  const int nConst = problem.nConst;
  // scenario
  const int stackLen = other.stackLen;
  // local variables
  kahan::kfloat64 sum_error = 0;
  if (idSol == 0) {
    std::cout << "DEBUG[idSol=0] BEGIN sum_error:" << sum_error << std::endl;
  }
  //
  const int realTests = problem.tests - training;
  for (int t = 0; t < realTests; t++) {
    std::stack<double> stk;
    int contSeed = 0;

    for (int j = 0; j < stackLen; j++) {
      // cout << "begin var i=" << i << " / sol_size=" << rep.vstack.size() <<
      // endl;
      //  case: push
      //  -1 0 1 2
      //  2 3
      // push variable or constant
      if ((individual[j] < 7500) && (individual[j] >= 5000)) {
        int my_floor =
            ::floor((individual[stackLen + j] / 10000.0) * (nVars + nConst));
        int idVar = my_floor - nConst;
        if (idSol == 0 && t == 0) {
          std::cout << "DEBUG[idSol=0] idVar=" << idVar << std::endl;
        }
        // printf("%d\n",idVar);
        double varValue = 0;
        // push variable
        if (idVar >= 0) {
          varValue = problem.inputs[t][idVar];
          stk.push(varValue);
          if (idSol == 0 && t == 0) {
            std::cout << "DEBUG[idSol=0] pushvar: " << varValue << std::endl;
          }
        } else {
          // push constant
          idVar += nConst;
          if (problem.vConst[idVar].first == problem.vConst[idVar].second) {
            varValue = problem.vConst[idVar].first;
            stk.push(varValue);
          } else {
            chromosome seedConst = individual[3 * stackLen + contSeed];
            srand(seedConst);
            // NOLINTNEXTLINE
            varValue = rand() % (int)(problem.vConst[idVar].second -
                                      problem.vConst[idVar].first + 1) +
                       problem.vConst[idVar].first;
            stk.push(varValue);
            contSeed++;
          }
        }
      }

      // case: pop Binary Operation
      if (individual[j] < 2500) {
        // pop operation
        int idOpBi = floor(
            (individual[2 * stackLen + j] / 10000.0) *
            (double)other.operationsBi.size());  // 4 is lenght of operationBi
        // assert(idOp != -1); // guarantee that it's not "disabled" (-1)
        //
        if (idSol == 0 && t == 0) {
          std::cout << "DEBUG[idSol=0] idOpBi=" << idOpBi << std::endl;
        }
        double v1 = stk.top();
        stk.pop();
        double v2 = stk.top();
        stk.pop();
        // RETORNAR opcional VAZIO!
        double binaryProduct = execBinaryOp(idOpBi, v1, v2, other.operationsBi);
        // if for case: division by zero
        if (abs(binaryProduct) == INFINITY) {
          //
          // std::cout << "WARNING: INFINITY!" << std::endl;
          //
          while (stk.size() > 0) stk.pop();
          stk.push(INFINITY);
          // =========================================
          // MUITO IMPORTANTE!!!
          // TODO: AVALIAR SE ISSO É UM BREAK MESMO...
          // =========================================
          // j = stackLen;  // break?
          //
          // SIGNIFICA QUE O ERRO DEVE SER INFINITO!!!
          // EXPRESSÃO MAL FORMADA!!!
          // PENALIZAR MUUUUUITO ALTO!!!
          break;
        } else {
          if (idSol == 0 && t == 0) {
            std::cout << "DEBUG[idSol=0] bin result: " << binaryProduct
                      << std::endl;
          }
          stk.push(binaryProduct);
        }
      }

      // pop: Unary Operation
      if ((individual[j] < 5000) && (individual[j] >= 2500)) {
        int idOpU = floor(
            (individual[2 * stackLen + j] / 10000.0) *
            (double)other.operationsU.size());  // 3 is lenght of operationU
        // assert(idOp != -1); // guarantee that it's not "disabled" (-1)
        //
        if (idSol == 0 && t == 0) {
          std::cout << "DEBUG[idSol=0] idOpU=" << idOpU << std::endl;
        }
        double v1 = stk.top();
        stk.pop();

        double unResult = execUnaryOp(idOpU, v1, other.operationsU);
        if (idSol == 0 && t == 0) {
          std::cout << "DEBUG[idSol=0] un func: " << other.operationsU[idOpU]
                    << " un param:" << v1 << std::endl;
          std::cout << "DEBUG[idSol=0] un result: " << unResult << std::endl;
        }
        stk.push(unResult);
      }

      if (individual[j] >= 7500) {
        if (idSol == 0 && t == 0) {
          std::cout << "DEBUG[idSol=0] NOP" << std::endl;
        }
        //
        // cout << "i=" << i << " -> stack size = " << stk.size() << endl;
      }

      //
      // cout << "finished t= " << t << endl;
      // take value from stack
      // assert(stk.size() == 1);
      //
    }  // for j < stackLen

    double val = stk.top();
    stk.pop();
    //
    // compare with expected value

    if (idSol == 0 && t == 0) {
      std::cout << "DEBUG[idSol=0] val:" << val << std::endl;
      std::cout << "DEBUG[idSol=0] expected:" << problem.outputs[t]
                << std::endl;
      std::cout << "DEBUG[idSol=0] BEFORE sum_error:" << sum_error << std::endl;
    }

    sum_error += computeError(val, problem.outputs[t]);

    if (idSol == 0 && t == 0) {
      std::cout << "DEBUG[idSol=0] AFTER sum_error:" << sum_error << std::endl;
    }
    // printf("sum_error = %lf\n",sum_error);
  }
  // average erro
  double solutionValue = (double)sum_error / realTests;

  if (idSol == 0) {
    std::cout << "DEBUG[idSol=0] Final sum_error:" << sum_error << std::endl;
    std::cout << "DEBUG[idSol=0] Final solutionValue:" << solutionValue
              << std::endl;
  }
  // printf("solutionValue = %lf\n",solutionValue);
  // printf("sum_error = %f solutionValue = %f\n",sum_error,solutionValue);
  // printf("%f\n",solutionValue);
  return solutionValue;
}
