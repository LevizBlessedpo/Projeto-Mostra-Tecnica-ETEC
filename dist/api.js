import { GEMINI_API_KEY } from "./config.js";
// Endpoint oficial da API REST v1beta
const url = `https://generativelanguage.googleapis.com/v1beta/models/gemini-3.7-flash:generateContent?key=${GEMINI_API_KEY}`;
// Objeto de instrução do sistema
const systemInstruction = {
    parts: [
        {
            text: "Você deverá responder perguntas de maneira clara e sucinta de maneira que pessoas leigas possam entender. Evite respostas longas e complexas. O nosso projeto conta com um circuito que utiliza um microcontrolador ESP32, sensor de temperatura e umidade DHT11, e um display LCD com módulo I2C para exibir informações em tempo real. O sistema é alimentado por uma fonte de energia externa pelo usb do computador e possui conectividade bluetooth para enviar dados para a nuvem. O código do projeto é escrito em C++ utilizando a plataforma Arduino IDE, o nosso site aonde ficará disponível a informação dos componentes explicação de funcionalidades do projeto etc.. Ajude as pessoas que te perguntarem sobre o site de maneira explicável pois pessoas leigas também vão estar acessando. Responda perguntas que tenham a ver com essas informações, quaisquer outras perguntas que não sejam relacionadas a essas informações apenas diga 'Desculpe, não entendi a pergunta.', certifique-se de fornecer respostas que estejam alinhadas com essas informações."
        }
    ]
};
export async function chamarGeminiAPI(perguntaDoUsuario) {
    try {
        const response = await fetch(url, {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({
                systemInstruction: systemInstruction, // Alterado para camelCase (sem sublinhado)
                contents: [
                    {
                        parts: [{ text: perguntaDoUsuario }]
                    }
                ]
            })
        });
        if (!response.ok) {
            const erroDetalhado = await response.json().catch(() => null);
            console.error("Detalhes do erro retornado pela API:", erroDetalhado);
            throw new Error(`Erro na requisição: ${response.status}`);
        }
        const dados = await response.json();
        // Retorna a resposta extraída do JSON do Gemini
        return dados.candidates[0].content.parts[0].text;
    }
    catch (erro) {
        console.error("Ocorreu um erro ao chamar a API do Gemini:", erro);
        return "Houve um problema na IA ao tentar responder.";
    }
}
//# sourceMappingURL=api.js.map