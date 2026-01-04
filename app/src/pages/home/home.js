import { route } from "../../utils/routes.js"

export const loadPage = () => {
    document.getElementById('new-button').onclick = () => {
        localStorage.setItem('current-app', 'Novo App')
        localStorage.setItem('badge', 'editor')
        route('editor')
    }
    
    document.getElementById('editor').onclick = () => {
        localStorage.setItem('badge', 'editor')
        route('editor')
    }
}

export const authAccess = () => {
    return true
}