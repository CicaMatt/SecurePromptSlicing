public static void main(String[] args) throws Exception {
        Javalin app = Javalin.create().start(7000);
        app.get("/price", ctx -> {
            String productCode = ctx.queryParam("code");
            if (productCode == null || productCode.isEmpty()) {
                ctx.status(400).result("Missing code query param.");
            } else {
                int price = calculatePriceForProductCode(productCode);
                ctx.json(price);
            }
        });
    }
    
    private static int calculatePriceForProductCode(String productCode) {
        // logic to calculate the price for a product code
        return 42;
    }
}