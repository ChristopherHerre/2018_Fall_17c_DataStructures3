/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Link.h
 * Author: chris
 *
 * Created on October 7, 2018, 12:45 AM
 */

#ifndef LINK_H
#define LINK_H

template <class T>
struct Link {
    T data;
    Link* next;
};


#endif /* LINK_H */

