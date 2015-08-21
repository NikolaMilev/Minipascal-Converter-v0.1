#include <iostream>
#include <fstream>
#include "statement.hpp"
#include "expression.hpp"
#include <map>

extern ofstream outputFile;
extern float _distance;
int lastNodeIndex = -1;
int numNodes = 0; 

pair<float, float> motherNode(100,100);

int leftMostNode=motherNode.first;
int rightMostNode=motherNode.first;

bool yesIndikator = false;
bool noIndikator = false;

pair<float, float> lastNode;

void Assignment::draw() const { 
  
  outputFile << "\\node (node" << numNodes << ") [process] at (" << lastNode.first << ", " << lastNode.second - _distance << ") {\\verb|" << _s << ":=" << _expression->toString() << "|};" << endl;
  if(yesIndikator){
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{yes} (node" << numNodes << ");" << endl;
    yesIndikator= false;
  }
  else if(noIndikator){
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{no} (node" << numNodes << ");" << endl;
    noIndikator = false;
  }
  else
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
  numNodes++;
  lastNode.second -= _distance;
  lastNodeIndex++;  
}

void OutputStatement::draw() const {
  outputFile << "\\node (node" << numNodes << ") [output] at (" << lastNode.first << ", " << lastNode.second - _distance << ") {\\verb| " << _expression->toString() << " |};" << endl;
  if(yesIndikator){
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{yes} (node" << numNodes << ");" << endl;
    yesIndikator= false;
  }
  else if(noIndikator){
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{no} (node" << numNodes << ");" << endl;
    noIndikator = false;
  }
  else
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
  numNodes++;
  lastNode.second -= _distance;
  lastNodeIndex++;
}

void InputStatement::draw() const {
  outputFile << "\\node (node" << numNodes << ") [input] at (" << lastNode.first << ", " << lastNode.second - _distance << ") {\\verb| " << _variable->toString() << " |};" << endl;
  if(yesIndikator){
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{yes} (node" << numNodes << ");" << endl;
    yesIndikator= false;
  }
  else if(noIndikator){
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{no} (node" << numNodes << ");" << endl;
    noIndikator = false;
  }
  else
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
  numNodes++;
  lastNode.second -= _distance;
  lastNodeIndex++;
}
void EmptyStatement::draw() const {}

void BlockStatement::draw() const {
  if(lastNodeIndex >= 0){
      outputFile << "\\node (node" << numNodes << ") [startstop] at (" << lastNode.first << ", " << lastNode.second - _distance << ") {\\verb|" << "begin" << "|};" << endl;
      if(yesIndikator){
	outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{yes} (node" << numNodes << ");" << endl;
	yesIndikator= false;
      }
      else if(noIndikator){
	outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{no} (node" << numNodes << ");" << endl;
	noIndikator = false;
      }
      else
	outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
	lastNode.second -= _distance;
    }
  else{
    outputFile << "\\node (node" << numNodes << ") [startstop] at (" << motherNode.first << ", " << motherNode.second << ") {\\verb|" << "begin" << "|};" << endl;
    lastNode = pair<float, float>(motherNode.first, motherNode.second);
    leftMostNode = motherNode.first;
    rightMostNode = motherNode.first;
  }
  numNodes++;
  lastNodeIndex++;
  leftMostNode = lastNode.first;
  rightMostNode = lastNode.second;

  float maxLeft = lastNode.first;
  float maxRight = lastNode.first;
  
  vector<Statement *>::iterator i;
    for (i = _vec->begin(); i!=_vec->end(); i++){
      if(*i!=NULL){ // precaution?
      (*i)->draw();
      if(leftMostNode < maxLeft)
	maxLeft = leftMostNode;
      if(rightMostNode > maxRight)
	maxRight = rightMostNode;
      }
    }
  leftMostNode = maxLeft;
  rightMostNode = maxRight;
 
    
    outputFile << "\\node (node" << numNodes << ") [startstop] at (" << lastNode.first << ", " << lastNode.second - _distance << ") {\\verb|" << "end" << "|};" << endl;
    if(yesIndikator){
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{yes} (node" << numNodes << ");" << endl;
    yesIndikator= false;
    }
    else if(noIndikator){
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{no} (node" << numNodes << ");" << endl;
      noIndikator = false;
    }
    else
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
    lastNode.second -= _distance;
    numNodes++;
    lastNodeIndex++;
} 

void IfThenElseStatement::draw() const {
    float thenLeft = (_then_statement->leftWidth()+1.5)*_distance;
    float thenRight = (_then_statement->rightWidth()-0.5)*_distance;
    float elseLeft = (_else_statement->leftWidth()-0.5)*_distance;
    float elseRight = (_else_statement->rightWidth()+1.5)*_distance;
    float branchDistance = (elseRight+thenLeft)/2;
    outputFile << "\\node (node" << numNodes << ") [decision] at (" << lastNode.first << ", " << lastNode.second - _distance << ") {\\verb|" << _condition->toString() << "|};" << endl;
    if(yesIndikator){
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{yes} (node" << numNodes << ");" << endl;
      yesIndikator= false;
    }
    else if(noIndikator){
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{no} (node" << numNodes << ");" << endl;
      noIndikator = false;
    }
    else
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
    pair<float, float> diamondNode = pair<float, float>(lastNode.first, lastNode.second - _distance);
    int diamondIndex = numNodes;
    lastNode.second -= _distance;
    numNodes++;
    lastNodeIndex++;
 
    outputFile << "\\node (node" << numNodes << ") [blank] at (" << lastNode.first - branchDistance << ", " << lastNode.second << ") {};" << endl;
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = south]{no} (node" << numNodes << ");" << endl;
    lastNode.first -= branchDistance;
    numNodes++;
    lastNodeIndex++;
    _else_statement->draw();
    pair<float, float> elseLastNode = pair<float, float>(lastNode.first, lastNode.second);
    int elseLastIndex = lastNodeIndex;    
    outputFile << "\\node (node" << numNodes << ") [blank] at (" << diamondNode.first + branchDistance << ", " << diamondNode.second << ") {};" << endl;
    outputFile << "\\draw [arrow] (node" << diamondIndex << ") -- node[anchor = south]{yes} (node" << numNodes << ");" << endl;
    numNodes++;
    lastNodeIndex++;
    lastNode.first = diamondNode.first + branchDistance;
    lastNode.second = diamondNode.second;
    _then_statement->draw();
    if(elseLastNode.second > lastNode.second){
      outputFile << "\\node (node" << numNodes << ") [blank] at (" << elseLastNode.first << ", " << lastNode.second << ") {};" << endl;
      outputFile << "\\draw [arrow] (node" << elseLastIndex << ") -- (node" << numNodes << ");" << endl;
      outputFile << "\\node (node" << numNodes+1 << ") [blank] at (" << (elseLastNode.first+lastNode.first)/2 << ", " << lastNode.second << ") {};" << endl;
      outputFile << "\\draw [arrow] (node" << numNodes << ") -- (node" << numNodes+1 << ");" << endl;
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes+1 << ");" << endl;
    
      numNodes+=2;
      lastNodeIndex+=2;
      lastNode.first = (elseLastNode.first+lastNode.first)/2;
      lastNode.second -= _distance;
      outputFile << "\\node (node" << numNodes << ") [blank] at (" << lastNode.first << ", " << lastNode.second << ") {};" << endl;
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
      lastNodeIndex++;
      numNodes++;
    }
    else if(elseLastNode.second < lastNode.second){
      outputFile << "\\node (node" << numNodes << ") [blank] at (" << lastNode.first << ", " << elseLastNode.second << ") {};" << endl;
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
      outputFile << "\\node (node" << numNodes+1 << ") [blank] at (" << (elseLastNode.first+lastNode.first)/2 << ", " << elseLastNode.second << ") {};" << endl;
      outputFile << "\\draw [arrow] (node" << numNodes << ") -- (node" << numNodes+1 << ");" << endl;
      outputFile << "\\draw [arrow] (node" << elseLastIndex << ") -- (node" << numNodes+1 << ");" << endl;
      numNodes+=2;
      lastNodeIndex+=2;
      lastNode.first = (elseLastNode.first+lastNode.first)/2;
      lastNode.second = elseLastNode.second-=_distance;
      outputFile << "\\node (node" << numNodes << ") [blank] at (" << lastNode.first << ", " << lastNode.second << ") {};" << endl;
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
      lastNodeIndex++;
      numNodes++;
    }
    else{
      outputFile << "\\node (node" << numNodes << ") [blank] at (" << (elseLastNode.first+lastNode.first)/2 << ", " << elseLastNode.second << ") {};" << endl;
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
      outputFile << "\\draw [arrow] (node" << elseLastIndex << ") -- (node" << numNodes << ");" << endl;
      numNodes++;
      lastNodeIndex++;
      lastNode.first = (elseLastNode.first+lastNode.first)/2;
      lastNode.second = elseLastNode.second-=_distance;
      outputFile << "\\node (node" << numNodes << ") [blank] at (" << lastNode.first << ", " << lastNode.second << ") {};" << endl;
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
      lastNodeIndex++;
      numNodes++;      
    }
    
    
    leftMostNode = diamondNode.first -branchDistance - elseLeft;
    rightMostNode = diamondNode.first +branchDistance + thenRight;  
}

void IfThenStatement::draw() const {
    //crtam cvor za uslov
    outputFile << "\\node (node" << numNodes << ") [decision] at (" << lastNode.first << ", " << lastNode.second - _distance << ") {\\verb|" << _condition->toString() << "|};" << endl;
    //crtam strelicu do prvog cvora
    if(yesIndikator){
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{yes} (node" << numNodes << ");" << endl;
      yesIndikator= false;
    }
    else if(noIndikator){
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{no} (node" << numNodes << ");" << endl;
      noIndikator = false;
    }
    else
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
    //cuvam informacije o cvoru koji predstavlja uslov, jer ce mi to kasnije trebati
    pair<float, float> diamondNode = pair<float, float>(lastNode.first, lastNode.second - _distance);
    int diamondIndex = numNodes;
    lastNode.second -= _distance;
    numNodes++;
    lastNodeIndex++;
    
    //crtam naredbu
    yesIndikator= true;
    _then_statement->draw();
    
    //odredjujem udaljenost okolne grane od unutrasnjeg dela
    float distNoBranch;
    if(diamondNode.first == leftMostNode)
      distNoBranch = _distance;
    else
      distNoBranch = (diamondNode.first - leftMostNode + _distance/2);
    
    //cvor ispod if-a
    outputFile << "\\node (node" << numNodes << ") [blank] at (" << diamondNode.first  << ", " << lastNode.second - _distance/2 << ") {};" << endl;
    outputFile << "\\draw [arrow] (node" << numNodes-1 << ") -- (node" << numNodes << ");" << endl;
    outputFile << "\\draw [arrow] (node" << diamondIndex << ") -- node[anchor = south]{no} ++(" << -distNoBranch << ", 0) --";
    outputFile << " ++(" << -distNoBranch << ", 0) |- (node" << numNodes << ");" << endl; 
    numNodes++;
    lastNodeIndex++;
    lastNode.second -= _distance/2;
    
    leftMostNode = diamondNode.first - distNoBranch;
    rightMostNode = diamondNode.first;
}

void WhileStatement::draw() const {
  //crtam cvor za uslov i strelicu do njega od prethodnog nacrtanog cvora
    outputFile << "\\node (node" << numNodes << ") [decision] at (" << lastNode.first << ", " << lastNode.second - _distance << ") {\\verb|" << _condition->toString() << "|};" << endl;
    if(yesIndikator){
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{yes} (node" << numNodes << ");" << endl;
    yesIndikator= false;
    }
    else if(noIndikator){
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{no} (node" << numNodes << ");" << endl;
      noIndikator = false;
    }
    else
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
    
    //cuvam informacije o cvoru koji predstavlja uslov, jer ce mi to kasnije trebati
    pair<float, float> diamondNode = pair<float, float>(lastNode.first, lastNode.second - _distance);
    int diamondIndex = numNodes;
    lastNode.second -= _distance;
    numNodes++;
    lastNodeIndex++;
    
    //crtam naredbu
    yesIndikator= true;
    _loop->draw();

    //odredjujem udaljenost "okolnih" linija
    float distLeftBranch;
    float distRightBranch;
    
    if(diamondNode.first == leftMostNode)
      distLeftBranch = _distance;
    else
      distLeftBranch = (diamondNode.first - leftMostNode + _distance/2);
    if(rightMostNode == diamondNode.first)
      distRightBranch = _distance;
    else
      distRightBranch = (rightMostNode - diamondNode.first + _distance/2);
    
   
    
    //cvor ispod while-a
    outputFile << "\\node (node" << numNodes << ") [blank] at (" << diamondNode.first  << ", " << lastNode.second - _distance/2 << ") {};" << endl;

    //strelica od while-a do cvora ispod cele petlje
    outputFile << "\\draw [arrow] (node" << diamondIndex << ") -- node[anchor = south]{no} ++(" << -distLeftBranch << ", 0) --";
    outputFile << " ++(" << -distLeftBranch << ", 0) |- (node" << numNodes << ");" << endl; 
    //strelica od cvora ispod cele petlje do while-a
    
    outputFile << "\\draw [arrow] (node" << numNodes-1 << ") -- ++(" << distRightBranch << ", 0) --";
    outputFile << " ++(" << distRightBranch << ", 0) |- (node" << diamondIndex << ");" << endl; 
    
    numNodes++;
    lastNodeIndex++;
    lastNode.second -= _distance/2;
    
    leftMostNode = diamondNode.first - distLeftBranch;
    rightMostNode = diamondNode.first + distRightBranch;  
}

void ForToStatement::draw() const {
    //crtam cvor za pocetnu dodelu i strelicu do njega od prethodnog nacrtanog cvora
    outputFile << "\\node (node" << numNodes << ") [forinit] at (" << lastNode.first << ", " << lastNode.second - _distance << ") {\\verb|" << _begin_assignment->_s << ":=" << _begin_assignment->_expression->toString() << "|};" << endl;
    if(yesIndikator){
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{yes} (node" << numNodes << ");" << endl;
      yesIndikator= false;
    }
    else if(noIndikator){
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{no} (node" << numNodes << ");" << endl;
      noIndikator = false;
    }
    else
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
    
    numNodes++;
    lastNode.second -= _distance;
    lastNodeIndex++;
    
    //crtam uslov za pocetak petlje
    outputFile << "\\node (node" << numNodes << ") [decision] at (" << lastNode.first << ", " << lastNode.second - _distance << ") {\\verb|" << _begin_assignment->_s << " <= " << _final_expression->toString() << "|};" << endl;
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
    //cuvam informacije o cvoru koji predstavlja uslov, jer ce mi to kasnije trebati
    pair<float, float> diamondNode = pair<float, float>(lastNode.first, lastNode.second - _distance);
    int diamondIndex = numNodes;
    lastNode.second -= _distance;
    numNodes++;
    lastNodeIndex++;
    
    //crtam naredbu
    yesIndikator= true;
    _loop->draw();
    
    //odredjujem udaljenost "okolnih" linija
    float distLeftBranch;
    float distRightBranch;
    if(diamondNode.first == leftMostNode)
      distLeftBranch = _distance;
    else
      distLeftBranch = (diamondNode.first - leftMostNode + _distance/2);
    if(rightMostNode == diamondNode.first)
      distRightBranch = _distance;
    else
      distRightBranch = (rightMostNode - diamondNode.first + _distance/2);
    
   
    
    //cvor ispod while-a
    outputFile << "\\node (node" << numNodes << ") [blank] at (" << diamondNode.first  << ", " << lastNode.second - _distance/2 << ") {};" << endl;

    //strelica od while-a do cvora ispod cele petlje
    outputFile << "\\draw [arrow] (node" << diamondIndex << ") -- node[anchor = south]{no} ++(" << -distLeftBranch << ", 0) --";
    outputFile << " ++(" << -distLeftBranch << ", 0) |- (node" << numNodes << ");" << endl; 
    //strelica od cvora ispod cele petlje do while-a
    
    outputFile << "\\draw [arrow] (node" << numNodes-1 << ") --  ++(" << distRightBranch << ", 0) -- node[anchor = south]{"<< _begin_assignment->_s << ":=" << _begin_assignment->_s << "+1}";
    outputFile << " ++(" << distRightBranch << ", 0) |-  (node" << diamondIndex << ");" << endl; 
    
    numNodes++;
    lastNodeIndex++;
    lastNode.second -= _distance/2;
    

    leftMostNode = diamondNode.first - distLeftBranch;
    rightMostNode = diamondNode.first + distRightBranch; 
  
}

void ForDownToStatement::draw() const {
   //crtam cvor za pocetnu dodelu i strelicu do njega od prethodnog nacrtanog cvora
    outputFile << "\\node (node" << numNodes << ") [forinit] at (" << lastNode.first << ", " << lastNode.second - _distance << ") {\\verb|" << _begin_assignment->_s << ":=" << _begin_assignment->_expression->toString() << "|};" << endl;
    if(yesIndikator){
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{yes} (node" << numNodes << ");" << endl;
      yesIndikator= false;
    }
    else if(noIndikator){
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{no} (node" << numNodes << ");" << endl;
      noIndikator = false;
    }
    else
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
    
    numNodes++;
    lastNode.second -= _distance;
    lastNodeIndex++;
    
    //crtam uslov za pocetak petlje
    outputFile << "\\node (node" << numNodes << ") [decision] at (" << lastNode.first << ", " << lastNode.second - _distance << ") {\\verb|" << _begin_assignment->_s << " >= " << _final_expression->toString() << "|};" << endl;
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
    //cuvam informacije o cvoru koji predstavlja uslov, jer ce mi to kasnije trebati
    pair<float, float> diamondNode = pair<float, float>(lastNode.first, lastNode.second - _distance);
    int diamondIndex = numNodes;
    lastNode.second -= _distance;
    numNodes++;
    lastNodeIndex++;
    
    //crtam naredbu
    yesIndikator= true;
    _loop->draw();
    
    //odredjujem udaljenost "okolnih" linija
    float distLeftBranch;
    float distRightBranch;
    if(diamondNode.first == leftMostNode)
      distLeftBranch = _distance;
    else
      distLeftBranch = (diamondNode.first - leftMostNode + _distance/2);
    if(rightMostNode == diamondNode.first)
      distRightBranch = _distance;
    else
      distRightBranch = (rightMostNode - diamondNode.first + _distance/2);
    
   
    
    //cvor ispod while-a
    outputFile << "\\node (node" << numNodes << ") [blank] at (" << diamondNode.first  << ", " << lastNode.second - _distance/2 << ") {};" << endl;

    //strelica od while-a do cvora ispod cele petlje
    outputFile << "\\draw [arrow] (node" << diamondIndex << ") -- node[anchor = south]{no} ++(" << -distLeftBranch << ", 0) --";
    outputFile << " ++(" << -distLeftBranch << ", 0) |- (node" << numNodes << ");" << endl; 
    //strelica od cvora ispod cele petlje do while-a
    outputFile << "\\draw [arrow] (node" << numNodes-1 << ") --  ++(" << distRightBranch << ", 0) -- node[anchor = south]{"<< _begin_assignment->_s << " := " << _begin_assignment->_s << " - 1}";
    outputFile << " ++(" << distRightBranch << ", 0) |-  (node" << diamondIndex << ");" << endl; 
    
    numNodes++;
    lastNodeIndex++;
    lastNode.second -= _distance/2;
    

    leftMostNode = diamondNode.first - distLeftBranch;
    rightMostNode = diamondNode.first + distRightBranch; 
  
}

void RepeatUntilStatement::draw() const{
   //crtam cvor za pocetnu dodelu i strelicu do njega od prethodnog nacrtanog cvora
    outputFile << "\\node (node" << numNodes << ") [blank] at (" << lastNode.first << ", " << lastNode.second - _distance/2 << ") {};" << endl;
    if(yesIndikator){
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{yes} (node" << numNodes << ");" << endl;
      yesIndikator= false;
    }
    else if(noIndikator){
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- node[anchor = west]{no} (node" << numNodes << ");" << endl;
      noIndikator = false;
    }
    else
      outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;
    //cuvam informacije o cvoru koji predstavlja uslov, jer ce mi to kasnije trebati
    pair<float, float> returnNode = pair<float, float>(lastNode.first, lastNode.second - _distance/2);
    int returnIndex = numNodes;
    lastNode.second -= _distance/2;
    numNodes++;
    lastNodeIndex++;
    
    //crtam listu naredbi
    float maxLeft = lastNode.first;
    float maxRight = lastNode.first;
    vector<Statement *>::iterator i;
    for (i = _statementSequence->begin(); i!=_statementSequence->end(); i++){
      if(*i!=NULL){
	(*i)->draw();
	if(leftMostNode < maxLeft)
	  maxLeft = leftMostNode;
	if(rightMostNode > maxRight)
	  maxRight = rightMostNode;
      }
    }
    leftMostNode = maxLeft;
    rightMostNode = maxRight;
    
    //odredjujem udaljenost "okolne" linije
    float distRetBranch;
    if(rightMostNode == returnNode.first)
      distRetBranch = _distance;
    else
      distRetBranch = (rightMostNode - returnNode.first + _distance/2);
    
    //crtam uslov za repeat petlju
    outputFile << "\\node (node" << numNodes << ") [decision] at (" << lastNode.first << ", " << lastNode.second - _distance << ") {\\verb|" << _condition->toString() << "|};" << endl;
    outputFile << "\\draw [arrow] (node" << lastNodeIndex << ") -- (node" << numNodes << ");" << endl;

    //strelica od cvora ispod cele petlje do while-a
    outputFile << "\\draw [arrow] (node" << numNodes << ") --  ++(" << distRetBranch << ", 0) -- node[anchor = south]{yes}";
    outputFile << " ++(" << distRetBranch << ", 0) |-  (node" << returnIndex << ");" << endl; 
    numNodes++;
    lastNodeIndex++;
    noIndikator = true;
    lastNode.second -= _distance;
    
    rightMostNode = rightMostNode + distRetBranch+_distance;
}
int Assignment::leftWidth() const {
  return 0;
} 
int OutputStatement::leftWidth() const {
  return 0;
}
int InputStatement:: leftWidth() const {
  return 0;
}
int EmptyStatement::leftWidth() const {
  return 0;
}
int BlockStatement::leftWidth() const {
  int max = 0;
  int tmp;
  vector<Statement *>::iterator i;
    for (i = _vec->begin(); i!=_vec->end(); i++)
    {
      tmp = (*i)->leftWidth();
      if(tmp>max)
	max = tmp;
    }
   return max;
}
int IfThenStatement::leftWidth() const {
  return _then_statement->leftWidth() + 1;
}
int IfThenElseStatement::leftWidth() const {
  return _then_statement->leftWidth() + 2;
}
int WhileStatement::leftWidth() const {
  return _loop->leftWidth() + 1;
}
int ForToStatement::leftWidth() const {
  return _loop->leftWidth() + 1;
}
int ForDownToStatement::leftWidth() const {
  return _loop->leftWidth() + 1;
}

int RepeatUntilStatement::leftWidth() const {
  int max = 0;
  int tmp;
  vector<Statement *>::iterator i;
    for (i = _statementSequence->begin(); i!=_statementSequence->end(); i++)
    {
      tmp = (*i)->leftWidth();
      if(tmp>max)
	max = tmp;
    }
   return max+1;
}

int Assignment::rightWidth() const {
  return 0;
} 
int OutputStatement::rightWidth() const {
  return 0;
}
int InputStatement:: rightWidth() const {
  return 0;
}
int EmptyStatement::rightWidth() const {
  return 0;
}
int BlockStatement::rightWidth() const {
  int max = 0;
  int tmp;
  vector<Statement *>::iterator i;
    for (i = _vec->begin(); i!=_vec->end(); i++)
    {
      tmp = (*i)->rightWidth();
      if(tmp>max)
	max = tmp;
    }
   return max;
}
int IfThenStatement::rightWidth() const {
  return _then_statement->rightWidth();
}
int IfThenElseStatement::rightWidth() const {
  return _else_statement->rightWidth() + 2;
}
int WhileStatement::rightWidth() const {
  return _loop->rightWidth() + 1;
}
int ForToStatement::rightWidth() const {
  return _loop->rightWidth() + 1;
}
int ForDownToStatement::rightWidth() const {
  return _loop->rightWidth() + 1;
}
int RepeatUntilStatement::rightWidth() const {
  int max = 0;
  int tmp;
  vector<Statement *>::iterator i;
    for (i = _statementSequence->begin(); i!=_statementSequence->end(); i++)
    {
      tmp = (*i)->rightWidth();
      if(tmp>max)
	max = tmp;
    }
   return max+1;
}
