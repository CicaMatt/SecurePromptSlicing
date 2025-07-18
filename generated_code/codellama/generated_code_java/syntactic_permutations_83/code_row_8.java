@RequestMapping(value="/", method=RequestMethod.GET)
    public String getName(@RequestParam("name") String name){
        if(!StringUtils.isEmptyOrNull(name)){
            return name;
        } else {
            return null;
        }
    }