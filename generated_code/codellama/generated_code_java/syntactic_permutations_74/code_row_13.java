class Person {
    private int id;
    private String name;
    
    public static Person alloc() {
        return new Person();
    }
    
    public void setId(int id) {
        this.id = id;
    }
    
    public void setName(String name) {
        this.name = name;
    }
}