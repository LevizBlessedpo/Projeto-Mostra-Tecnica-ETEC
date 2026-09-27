// Faz os elementos com a classe "fade-in" aparecerem suavemente
// conforme entram na área visível da tela durante a rolagem.
document.addEventListener('DOMContentLoaded', () => {
    const elementos = document.querySelectorAll('.fade-in');

    const observador = new IntersectionObserver((entradas) => {
        entradas.forEach((entrada) => {
            if (entrada.isIntersecting) {
                entrada.target.classList.add('visivel');
                // Depois de aparecer uma vez, para de observar
                observador.unobserve(entrada.target);
            }
        });
    }, {
        threshold: 0.15 // dispara quando 15% do elemento já está visível
    });

    elementos.forEach((el) => observador.observe(el));
});