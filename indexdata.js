const form = document.getElementById('form');
        const booktitle = document.getElementById('booktitle');
        const author = document.getElementById('author');

        form.addEventListener('submit', function(e) {
            e.preventDefault();

            const booktitleValue = booktitle.value;
            const authorValue = author.value;
            
            localStorage.setItem('booktitle', booktitleValue);
            localStorage.setItem('author', authorValue);

            window.location.href = "index2.html";
        })