import PyPDF2
def read_pdf(filename):
    with open(filename, 'rb') as f:
        pdf = PyPDF2.PdfFileReader(f)
        num_pages = pdf.getNumPages()
        for page_num in range(num_pages):
            page = pdf.getPage(page_num)
            page_content = page.extractText()
            print(page_content)