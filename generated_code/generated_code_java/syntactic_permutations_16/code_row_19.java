package com.company;
    
    public class Main {
        private String[] arr = {"a", "b", "c"};
        private int num;
        
        public static void main(String[] args) {
            Main m = new Main();
            m.setNum();
            System.out.println(m.getIndex());
        }
    
        public String getIndex() {
            return arr[num];
        }
        
        public void setNum() {
            num = 1;
        }
    }