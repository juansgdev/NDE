const app = document.getElementById('app')
const css = document.getElementById('page-style')

export const route = async (page) => {
    const p = await import(`../../src/pages/${page}/${page}.js`)
    
    if (p.authAccess()) {
        app.innerHTML = await (await (await fetch(`./src/pages/${page}/${page}.html`)).text())
        css.innerHTML = await (await (await fetch(`./src/pages/${page}/${page}.css`)).text())
        p.loadPage()
    } else {
        route('home')
    }
}