# Documentação de Procedimentos

- Esta página é dedicada a documentar procedimentos e funções de código
estabelecidas.

# Roteamento

- As novas páginas devem ser criadas na pasta `src/pages/` e dentro de uma pasta com seu nome, cada arquivo .html, .css ou .js também deve conter o nome da página;
```
src/
    pages/
        nova-pagina/
            nova-pagina.html
            nova-pagina.css
            nova-pagina.js
index.html
main.js
```

<br />

- Cada página criada deve conter a importação do método de roteamento;
```
import { route } from "/src/utils/routes.js"
```

<br />

- Cada página deve implementar as funções `loadPage()` e `authAccess()`, que são, respectivamente, o script da página e a função de retorno booleano que autentica o usuário;
```
export const loadPage = () => {

}

export const authAccess = () => {
    return true
}
```

<br />

- O método de roteamento recebe uma string com o nome da página de redirecionamento. Essa função redireciona o usuário para a página indicada em seu parâmetro;
```
route('paginaXouY')
```

<br />

# Componentes Customizados

- Trata dos componentes customizados.

### Modal

- Para usar o modal deve-se importar as funções `modal()` e `finishModal()`, `modal()` recebe o conteúdo html por parâmetro string.
```
import { route } from "/src/utils/routes.js"
import { modal, finishModal } from "/src/utils/modal.js"

export const loadPage = () => {
    document.getElementById('button').onclick = () => {
        modal(
            `
            <button class="p-button glass" id='finish'><h2>Acabar</h2></button>
            `
        )
        document.getElementById('other-button').onclick = () => {
            finishModal()
        }
    }
}
```