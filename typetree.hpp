#ifndef TYPETREE_HPP_INCLUDED
#define TYPETREE_HPP_INCLUDED
#include <vector>
#include <string>

struct pathType
{
    int depth;
    pathType * parent;
    std::vector<pathType*> children;
    std::string tag;
    bool root;
};

#endif // TYPETREE_HPP_INCLUDED
