class Person {
    private int status;
    
    public static Person alloc() {
        return (Person)(malloc(sizeof(Person)));
    }
}