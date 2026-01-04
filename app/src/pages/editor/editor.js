import { route } from "../../utils/routes.js"

export const loadPage = () => {
    const appName = document.getElementById('app-name')
    appName.value = localStorage.getItem('current-app')

    appName.oninput = () => {
        localStorage.setItem('current-app', appName.value)
        appName.value = localStorage.getItem('current-app')
    }

    document.getElementById('home').onclick = () => {
        route('home')
    }
}

export const authAccess = () => {
    return localStorage.getItem('badge') == 'editor'
}