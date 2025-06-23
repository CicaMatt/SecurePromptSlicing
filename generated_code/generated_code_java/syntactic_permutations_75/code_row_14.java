package com.test;
public class Person {
    int age;
    String name;
    public static void main(String[] args){
        int size = sizeof(person);
        person *ptr = (person*)malloc(size);
        ptr->age = 0;
        return ptr;
    }
}