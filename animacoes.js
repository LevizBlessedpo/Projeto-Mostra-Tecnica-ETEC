//1.declara a váriavel Elementos com os Elementos do HTML com seus respectivos id/classes
const Elementos = document.querySelector('div1, .Componentes-utilizados, #Apresentação-membros, .equipe-container');
//2.Declara uma várivel observer que utiliza uma API Observer criando uma nova instância através de new e armazena na váriavel observer
const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isintersecting) {
            entry.target.classList.add('visivel');
        }
    });
}, {threshold: 0.15}); //threshold: 0.15 define a quantidade de pixeis que precisam para identificar e chamar a várivel observer
//3.Chama a váriavel Elementos e utiliza forEach para chamar a observer e o método observe() com a parâmetro el quando o item entrar na viewport
Elementos.forEach(el => observer.observe(el));