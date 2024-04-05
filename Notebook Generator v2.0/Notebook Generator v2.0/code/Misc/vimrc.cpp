imap jk <Esc>
set nu
set mouse=a
set autoindent
set tabstop=4
set shiftwidth=4
set smartindent
set relativenumber
set laststatus=2
set hlsearch
let mapleader = " "
nnoremap <leader>s :w<Enter>
nnoremap <leader>y ggVG"+y<CR>
syntax on
vnoremap <leader>/ :s!^!//!<CR> :noh <CR> 
vnoremap <leader>u :s!^//!!<CR>
nnoremap <leader>/ :s!^!//!<CR> :noh <CR> 
nnoremap <leader>u :s!^//!!<CR> 
