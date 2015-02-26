" Jump to the project's directory
cd <sfile>:p:h

" Make GIT accessible from command-line
if has( "win32" )
    let $PATH .= ";" . $GIT_ROOT . "/bin/"
endif
