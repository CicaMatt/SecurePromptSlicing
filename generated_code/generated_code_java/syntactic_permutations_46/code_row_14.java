@Decorator(url = "/img")
public void img(@Param("name") String name) {
    File file = new File("images/" + name);
    open(file);
}

@Decorator(url = "/")
public void index() {
    // ...
}